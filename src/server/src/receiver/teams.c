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
    strcpy(data->teams[data->nbr_teams].name, recv_data.name);
    strcpy(data->teams[data->nbr_teams].description,
    recv_data.description);
    uuid_generate(data->teams[data->nbr_teams].teams_uuid);
    data->teams[data->nbr_teams].members_uuid = malloc(sizeof(uuid_t));
    data->teams[data->nbr_teams].members_uuid = NULL;
    data->teams[data->nbr_teams].subs_nbr = 0;
    return 0;
}

static int send_response(int client_fd, client_packet recv_data,
uuid_t team_uuid)
{
    char uuid_str[MAX_UUID_LENGTH];
    char team_str[MAX_UUID_LENGTH];
    server_packet data;

    uuid_unparse(recv_data.user_uuid, uuid_str);
    uuid_unparse(team_uuid, team_str);
    server_event_team_created(team_str, recv_data.name, uuid_str);
    data.type = TYPE_CREATE;
    data.user_name_len = strlen(recv_data.name) + 1;
    strcpy(data.name, recv_data.name);
    strcpy(data.description, recv_data.description);
    uuid_copy(data.team_uuid, team_uuid);
    data.code = CODE_200;
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

int receive_teams(data_t *data, int client_fd, client_packet recv_data)
{
    server_packet packet;
    user_t *user = index_of_user(data, recv_data.user_uuid);

    for (int i = 0; i < data->nbr_teams; i++)
        if (strcmp(data->teams[i].name, recv_data.name) == 0) {
            packet.code = CODE_400;
            packet.type = TYPE_CREATE;
            send(client_fd, &packet, sizeof(packet), 0);
            return 0;
        }
    create_teams(data, recv_data);
    send_response(client_fd, recv_data,
    data->teams[data->nbr_teams].teams_uuid);
    data->nbr_teams++;
    return 0;
}
