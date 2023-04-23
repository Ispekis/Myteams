/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribed
*/

#include "server.h"

int receive_subscribed(server_t *server, int index, client_packet recv_data)
{
    user_t *user;
    teams_t *team;

    if (uuid_is_null(recv_data.team_uuid)) {
        user = index_of_user(&server->data, recv_data.user_uuid);
        if (user == NULL)
            return 1;
        list_subscribed_team(server->data, *user,
        server->addrs.clients[index].fd);
    } else {
        team = index_of_team(&server->data, recv_data);
        if (team == NULL)
            return 1;
        list_subscribed_user(server->data, *team,
        server->addrs.clients[index].fd);
    }
    return 0;
}
