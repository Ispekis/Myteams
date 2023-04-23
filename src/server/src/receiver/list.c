/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** list
*/

#include "server.h"

int receive_list_teams(server_t *server, int index, client_packet recv_data)
{
    switch (recv_data.context) {
        case DEFAULT_CONTEXT:
            list_team(server->data,
            server->addrs.clients[index].fd, recv_data);
            break;
        case CHANNEL_CONTEXT:
            list_channel(server->data,
            server->addrs.clients[index].fd, recv_data);
            break;
        case THREAD_CONTEXT:
            list_thread(server->data,
            server->addrs.clients[index].fd, recv_data);
            break;
        case REPLY_CONTEXT:
            list_reply(server->data,
            server->addrs.clients[index].fd, recv_data);
            break;
    }
    return 0;
}
