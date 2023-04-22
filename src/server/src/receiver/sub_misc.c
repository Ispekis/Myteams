/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** unsub_misc
*/

#include "server.h"

int check_known(data_t *data, int client_fd, char *team_uuid,
int type)
{
    char tmp_uuid[37];
    server_packet packet;

    for (int i = 0; i < data->nbr_teams; ++i) {
        uuid_unparse(data->teams[i].teams_uuid, tmp_uuid);
        if (strcmp(tmp_uuid, team_uuid) == 0) {
            return 0;
        }
    }
    packet.type = type;
    packet.code = CODE_400;
    uuid_parse(team_uuid, packet.team_uuid);
    send(client_fd, &packet, sizeof(packet), 0);
    return -1;
}

int check_user_sub(server_t *server, char *user_uuid, char *team_uuid,
int index)
{
    /*size_t user = -1;
    size_t team = -1;
    char tmp_uuid[37];

    if (check_known(&server->data, server->addrs.clients[index].fd,
    team_uuid, TYPE_UNSUBSCRIBE) == -1)
        return -1;
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
    return user;*/
}
