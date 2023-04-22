/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribed
*/

#include "server.h"

int check_known(data_t *data, int client_fd, char *team_uuid,
int type);

static int subscribed_no_args(server_t *server, int index,
client_packet recv_data)
{
    char tmp_uuid[37];
    server_packet data;

    for (int i = 0; i < server->data.nbr_teams; ++i) {
        uuid_unparse(server->data.teams[i].teams_uuid, tmp_uuid);
        data.type = TYPE_SUBSCRIBED;
        uuid_parse(tmp_uuid, data.team_uuid);
        strcpy(data.team_name, server->data.teams[i].name);
        strcpy(data.description, server->data.teams[i].description);
        data.context = 0;
        send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    }
    return 0;
}

static int send_response_args(int client_fd, server_t *server,
int index)
{
    server_packet data;

    data.type = TYPE_SUBSCRIBED;
    uuid_copy(data.user_uuid, server->data.users[index].uuid);
    strcpy(data.name, server->data.users[index].name);
    data.status = server->data.users[index].is_logged;
    data.context = 1;
    data.code = CODE_200;
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

static int check_user(server_t *server, char *user_uuid)
{
    size_t user = -1;
    char tmp_uuid[37];

    for (int i = 0; i < server->data.nbr_users; ++i) {
        uuid_unparse(server->data.users[i].uuid, tmp_uuid);
        if (strcmp(tmp_uuid, user_uuid) == 0) {
            user = i;
            break;
        }
    }
    return user;
}

static int subscribed_args(server_t *server, int index, client_packet recv_data
, char *team_uuid)
{
    char tmp_uuid[37];
    size_t team = -1;
    size_t user = -1;

    for (int i = 0; i < server->data.nbr_teams; ++i) {
        uuid_unparse(server->data.teams[i].teams_uuid, tmp_uuid);
        team = strcmp(tmp_uuid, team_uuid) == 0 ? i : team;
    }
    if (team == -1)
        return 1;
    for (int i = 0; i < server->data.teams[team].subs_nbr; ++i) {
        strcpy(tmp_uuid, server->data.teams[team].team_member[i]);
        if ((user = check_user(server, tmp_uuid)) == -1)
            continue;
        send_response_args(server->addrs.clients[index].fd, server, user);
    }
    return 0;
}

int receive_subscribed(server_t *server, int index, client_packet recv_data)
{
    char tmp_uuid[37];

    if (recv_data.name_len == 0) {
        subscribed_no_args(server, index, recv_data);
    } else {
        uuid_unparse(recv_data.dest_uuid, tmp_uuid);
        if (check_known(&server->data, server->addrs.clients[index].fd,
        tmp_uuid, TYPE_SUBSCRIBED) == -1) {
            return 1;
        }
        subscribed_args(server, index, recv_data, tmp_uuid);
    }

    return 0;
}
