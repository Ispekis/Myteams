/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** use
*/

#include "server.h"

static int send_response(server_t *server, int index, client_packet recv_data)
{
    printf("ici\n");
    server_packet data;
    data.type = TYPE_USE;
    for (int i = 0; i < server->data.nbr_teams; i++) {
        if (uuid_compare(server->data.teams[i].teams_uuid,
        recv_data.dest_uuid) == 0) {
            data.context = TEAM_CONTEXT;
            send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
        } else {
            data.context = recv_data.context;
            send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
        }
    }
    return 0;
}

int receive_use(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    char team_uuid[37];
    data.type = TYPE_USE;

    uuid_unparse(recv_data.dest_uuid, team_uuid);
    if (uuid_is_null(recv_data.dest_uuid)) {
        data.context = DEFAULT_CONTEXT;
        send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    } else {
        send_response(server, index, recv_data);
    }
    return 0;
}
