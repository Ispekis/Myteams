/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** unsubscribe
*/

#include "server.h"

static int find_team_index(data_t *data, char *user_uuid, int index)
{
    size_t user = -1;
    char user_uuid_tmp[37];

    for (int i = 0; i < data->teams[index].subs_nbr; ++i) {
        uuid_unparse(data->users[i].uuid, user_uuid_tmp);
        user = strcmp(user_uuid_tmp, user_uuid) == 0 ? i : user;
    }
}

static int remove_member_team(data_t *data, char *user_uuid, char *team_uuid,
int index)
{
    size_t team = -1;
    char uuid_tmp[37];

    for (int i = 0; i < data->users[index].nbr_teams; ++i) {
        strcpy(uuid_tmp, data->users[index].subbed_teams[i]);
        team = strcmp(team_uuid, uuid_tmp) == 0 ? i : team;
    }
    if (team == -1)
        return 1;
    for (int i = (int)team; data->users[index].subbed_teams[i + 1]
    != NULL; ++i)
        strcpy(data->users[index].subbed_teams[i],
        data->users[index].subbed_teams[i + i]);
    data->users[index].nbr_teams--;
    data->users[index].subbed_teams = realloc(data->users[index].subbed_teams,
    (data->users[index].nbr_teams + 1) * (sizeof(char*)));
    data->users[index].subbed_teams[data->users[index].nbr_teams] = NULL;
    return 0;
}

static int leave_teams(data_t *data, char *user_uuid, char *team_uuid)
{
    size_t user = -1;
    size_t team = -1;
    char user_uuid_tmp[37];

    for (int i = 0; i < data->nbr_teams; ++i) {
        strcpy(user_uuid_tmp, data->teams[i].teams_uuid);
        team = strcmp(user_uuid_tmp, team_uuid) == 0 ? i : team;
    }
    if (team == -1 || (user = find_team_index(data, user_uuid, user)) == -1)
        return 1;
    for (int i = (int)user; data->teams[user].team_member[i + i] != NULL; ++i)
        strcpy(data->teams[user].team_member[i],
        data->teams[user].team_member[i + i]);
    data->teams->subs_nbr--;
    data->teams->team_member = realloc(data->teams->team_member,
    (data->teams->subs_nbr + 1) * (sizeof(char *)));
    data->teams->team_member[data->teams->subs_nbr] = NULL;
    return 0;
}

static int send_response(server_t *server, char *team_uuid, char *user_uuid,
int index)
{
    server_packet data;

    leave_teams(&server->data, user_uuid, team_uuid);
    server_event_user_unsubscribed(team_uuid, user_uuid);
    data.type = TYPE_UNSUBSCRIBE;
    uuid_parse(team_uuid, data.team_uuid);
    uuid_parse(user_uuid, data.user_uuid);
    send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    return 0;
}

int receive_unsubscribe(server_t *server, int index, client_packet recv_data)
{
    char user_uuid[37];
    char team_uuid[37];
    size_t user = -1;

    uuid_unparse(recv_data.user_uuid, user_uuid);
    for (int i = 0; i < server->data.nbr_users; ++i) {
        uuid_unparse(server->data.users[i].uuid, team_uuid);
        user = strcmp(team_uuid, user_uuid) == 0 ? i : user;
    }
    uuid_unparse(recv_data.dest_uuid, user_uuid);
    for (int i = 0; i < server->data.users[user].nbr_teams; ++i) {
        strcpy(team_uuid, server->data.users[user].subbed_teams[i]);
        if (strcmp(user_uuid, team_uuid) == 0) {
            uuid_unparse(recv_data.user_uuid, user_uuid);
            remove_member_team(&server->data, user_uuid, team_uuid, i);
            send_response(server, team_uuid, user_uuid, index);
        }
    }
    return 0;
}
