/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** info
*/

#include "server.h"

static void choose_info(user_t user, int client_fd, client_packet recv_data)
{
    switch (recv_data.context) {
        case TEAM_CONTEXT:
            printf("team\n");
            break;
        case CHANNEL_CONTEXT:
            printf("channel\n");
            break;
        case THREAD_CONTEXT:
            printf("thread\n");
            break;
        default:
            break;
    }
}

int receive_info(server_t *server, int index, client_packet recv_data)
{
    for (int i = 0; i < server->data.nbr_users; i++) {
        if (uuid_compare(server->data.users[i].uuid, recv_data.user_uuid) == 0)
            choose_info(server->data.users[i], server->addrs.clients->fd,
            recv_data);
    }
    return 0;
}
