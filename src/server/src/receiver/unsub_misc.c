/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** unsub_misc
*/

#include "server.h"

int find_team_index(data_t *data, char *user_uuid, int index)
{
    size_t user = -1;
    char user_uuid_tmp[37];

    for (int i = 0; i < data->teams[index].subs_nbr; ++i) {
        strcpy(user_uuid_tmp, data->teams[index].team_member[i]);
        user = strcmp(user_uuid_tmp, user_uuid) == 0 ? i : user;
    }
    return user;
}

int check_user_sub(server_t *server, char *user_uuid, char *team_uuid)
{
    size_t user = -1;
    size_t team = -1;
    char tmp_uuid[37];

    for (int i = 0; i < server->data.nbr_users; ++i) {
        uuid_unparse(server->data.users[i].uuid, tmp_uuid);
        user = strcmp(tmp_uuid, user_uuid) == 0 ? i : user;
    }
    if (user == -1)
        return -1;
    for (int i = 0; i < server->data.users[user].nbr_teams; ++i) {
        strcpy(tmp_uuid, server->data.users[user].subbed_teams[i]);
        team = strcmp(team_uuid, tmp_uuid) == 0 ? i : team;
    }
    if (team == -1)
        return -1;
    return user;
}
