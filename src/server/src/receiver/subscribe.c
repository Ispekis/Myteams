/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribe
*/

#include "server.h"

int check_known(data_t *data, int client_fd, char *team_uuid,
int type);

int member_add_team(data_t *data, char *user_uuid, char *team_uuid)
{
    size_t user = -1;
    char user_uuid_tmp[37];

    for (int i = 0; i < data->nbr_users; ++i) {
        uuid_unparse(data->users[i].uuid, user_uuid_tmp);
        user = strcmp(user_uuid_tmp, user_uuid) == 0 ? i : user;
    }
    if (user == -1)
        return 1;
    data->users[user].nbr_teams++;
    data->users[user].subbed_teams = realloc(data->users[user].subbed_teams,
    (data->users[user].nbr_teams + 1) * (sizeof(char*)));
    data->users[user].subbed_teams[data->users[user].nbr_teams - 1] =
    realloc(data->users[user].subbed_teams[data->users[user].nbr_teams - 1],
    sizeof(char) * 37);
    data->users[user].subbed_teams[data->users[user].nbr_teams - 1][36] = '\0';
    data->users[user].subbed_teams[data->users[user].nbr_teams] = NULL;
    strcpy(data->users[user].subbed_teams[data->users[user]
    .nbr_teams - 1], team_uuid);
    return 0;
}

int join_teams(data_t *data, char *user_uuid, char *team_uuid)
{
    size_t team = -1;
    char uuid_tmp[37];

    for (int i = 0; i < data->nbr_teams; ++i) {
        uuid_unparse(data->teams[i].teams_uuid, uuid_tmp);
        team = strcmp(uuid_tmp, team_uuid) == 0 ? i : team;
    }
    if (team == -1)
        return 1;
    data->teams[team].subs_nbr++;
    data->teams[team].team_member = realloc(data->teams[team].team_member,
    (data->teams[team].subs_nbr + 1) * (sizeof(char *)));
    data->teams[team].team_member[data->teams[team].subs_nbr - 1] = realloc
    (data->teams[team].team_member[data->teams[team].subs_nbr - 1],
    sizeof(char) * 37);
    data->teams[team].team_member[data->teams[team].subs_nbr - 1][36] = '\0';
    data->teams[team].team_member[data->teams[team].subs_nbr] = NULL;
    strcpy(data->teams[team].team_member[data->teams[team].subs_nbr - 1],
    user_uuid);
    return 0;
}

static int send_response(int client_fd, char *team_uuid, char *user_uuid)
{
    server_packet data;

    server_event_user_subscribed(team_uuid, user_uuid);
    data.type = TYPE_SUBSCRIBE;
    uuid_parse(team_uuid, data.team_uuid);
    uuid_parse(user_uuid, data.user_uuid);
    data.code = CODE_200;
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

int is_subscribed(data_t *data, client_packet recv_data, char *param_uuid,
int client_fd)
{
    size_t user = -1;
    char user_uuid_tmp[37];
    char real_user[37];

    if (check_known(data, client_fd, param_uuid, TYPE_SUBSCRIBE) == -1)
        return -1;
    uuid_unparse(recv_data.user_uuid, real_user);
    for (int i = 0; i < data->nbr_users; ++i) {
        uuid_unparse(data->users[i].uuid, user_uuid_tmp);
        user = strcmp(user_uuid_tmp, real_user) == 0 ? i : user;
    }
    if (user == -1)
        return -1;
    for (int i = 0; i < data->users[user].nbr_teams; ++i) {
        if (strcmp(data->users[user].subbed_teams[i], param_uuid) == 0)
            return -1;
    }
    return 0;
}

int receive_subscribe(server_t *server, int index, client_packet recv_data)
{
    char user_uuid[37];
    char team_uuid[37];

    uuid_unparse(recv_data.dest_uuid, user_uuid);
    if (is_subscribed(&server->data, recv_data, user_uuid,
    server->addrs.clients[index].fd) == -1)
        return 1;
    for (int i = 0; i < server->data.nbr_teams; ++i) {
        uuid_unparse(server->data.teams[i].teams_uuid, team_uuid);
        if (strcmp(user_uuid, team_uuid) == 0) {
            uuid_unparse(recv_data.user_uuid, user_uuid);
            join_teams(&server->data, user_uuid, team_uuid);
            member_add_team(&server->data, user_uuid, team_uuid);
            send_response(server->addrs.clients[index].fd, team_uuid,
            user_uuid);
            return 0;
        }
    }
    return 0;
}
