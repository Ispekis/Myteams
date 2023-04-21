/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** teams
*/

#include "server.h"

static int create_teams(data_t *data, client_packet recv_data)
{
    teams_t* new_team = realloc(data->teams,
    (data->nbr_teams + 1) * (sizeof(teams_t)));
    if (new_team == NULL)
        return 1;

    data->teams = new_team;
    data->teams[data->nbr_teams].name =
    malloc(sizeof(char) * (strlen(recv_data.name) + 1));
    if (data->teams[data->nbr_teams].name == NULL)
        return 1;
    strcpy(data->teams[data->nbr_teams].name, recv_data.name);
    strcpy(data->teams[data->nbr_teams].description,
    recv_data.description);
    uuid_generate(data->teams[data->nbr_teams].teams_uuid);
    data->teams[data->nbr_teams].team_member =
    malloc(sizeof(char *) + 1);
    data->teams[data->nbr_teams].team_member[0] = NULL;
    data->teams[data->nbr_teams].subs_nbr = 0;
    data->nbr_teams++;
    return 0;
}

static int send_response(int client_fd, client_packet recv_data,
char *team_uuid, char *user_uuid)
{
    server_packet data;

    server_event_team_created(team_uuid, recv_data.name, user_uuid);
    data.type = TYPE_CREATE;
    data.user_name_len = strlen(recv_data.name) + 1;
    strcpy(data.name, recv_data.name);
    strcpy(data.description, recv_data.description);
    uuid_parse(team_uuid, data.team_uuid);
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

int receive_teams(data_t *data, int client_fd, client_packet recv_data)
{
    char user_uuid[37];
    char team_uuid[37];

    for (int i = 0; i < data->nbr_teams; i++)
        if (strcmp(data->teams[i].name, recv_data.name) == 0) {
            return 1;
        }
    uuid_unparse(recv_data.user_uuid, user_uuid);
    create_teams(data, recv_data);
    uuid_unparse(data->teams[data->nbr_teams - 1].teams_uuid,
    team_uuid);
    join_teams(data, user_uuid, team_uuid);
    member_add_team(data, user_uuid, team_uuid);
    send_response(client_fd, recv_data,
    team_uuid, user_uuid);
    return 0;
}
