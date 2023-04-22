/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** info
*/

#include "server.h"

static void choose_info(data_t data, int client_fd, client_packet recv_data)
{
    switch (recv_data.context) {
        case REPLY_CONTEXT:
            info_thread(data, client_fd, recv_data);
            break;
        case CHANNEL_CONTEXT:
            info_team(data, client_fd, recv_data);
            break;
        case THREAD_CONTEXT:
            info_channel(data, client_fd, recv_data);
            break;
        default:
            break;
    }
}

int receive_info(server_t *server, int index, client_packet recv_data)
{
    choose_info(server->data, server->addrs.clients[index].fd, recv_data);
    return 0;
}
