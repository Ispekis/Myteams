/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** teams
*/

#include "server.h"

static int create_teams(server_t *server, client_packet recv_data)
{
    teams_t* new_team = realloc(server->data.teams,
    (server->data.nbr_teams + 1) * (sizeof(teams_t)));
    if (new_team == NULL)
        return 1;

    server->data.teams = new_team;
    server->data.teams[server->data.nbr_teams].name =
    malloc(sizeof(char) * (strlen(recv_data.name) + 1));
    if (server->data.teams[server->data.nbr_teams].name == NULL)
        return 1;
    strcpy(server->data.teams[server->data.nbr_teams].name, recv_data.name);
    strcpy(server->data.teams[server->data.nbr_teams].description,
    recv_data.description);
    uuid_generate(server->data.teams[server->data.nbr_teams].teams_uuid);
    server->data.teams[server->data.nbr_teams].team_member =
    malloc(sizeof(char *) + 1);
    server->data.teams[server->data.nbr_teams].team_member[0] = NULL;
    server->data.teams[server->data.nbr_teams].subs_nbr = 0;
    server->data.nbr_teams++;
    return 0;
}

static int send_response(int client_fd, client_packet recv_data,
char *team_uuid, char *user_uuid)
{
    server_packet data;

    server_event_team_created(team_uuid, recv_data.name, user_uuid);
    data.type = TYPE_CREATE_TEAM;
    data.user_name_len = strlen(recv_data.name) + 1;
    strcpy(data.name, recv_data.name);
    strcpy(data.description, recv_data.description);
    uuid_parse(team_uuid, data.team_uuid);
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

int receive_teams(server_t *server, int index, client_packet recv_data)
{
    char user_uuid[37];
    char team_uuid[37];

    for (int i = 0; i < server->data.nbr_teams; i++)
        if (strcmp(server->data.teams[i].name, recv_data.name) == 0) {
            return 1;
        }
    uuid_unparse(recv_data.user_uuid, user_uuid);
    create_teams(server, recv_data);
    uuid_unparse(server->data.teams[server->data.nbr_teams - 1].teams_uuid,
    team_uuid);
    join_teams(&server->data, user_uuid, team_uuid);
    member_add_team(&server->data, user_uuid, team_uuid);
    send_response(server->addrs.clients[index].fd, recv_data,
    team_uuid, user_uuid);
    return 0;
}
