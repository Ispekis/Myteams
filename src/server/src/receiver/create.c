/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create
*/

#include "server.h"

static void choose_create(data_t *data, int client_fd, client_packet recv_data)
{
    switch (recv_data.context) {
        case DEFAULT_CONTEXT:
            receive_teams(data, client_fd, recv_data);
            break;
        case REPLY_CONTEXT:
            create_reply(data, client_fd, recv_data);
            break;
        case CHANNEL_CONTEXT:
            printf("Channel\n");
            break;
        case THREAD_CONTEXT:
            create_thread(data, client_fd, recv_data);
            break;
    }
}

int receive_create(server_t *server, int index, client_packet recv_data)
{
    for (int i = 0; i < server->data.nbr_users; i++) {
        if (uuid_compare(server->data.users[i].uuid,
            recv_data.user_uuid) == 0) {
            choose_create(&server->data,
            server->addrs.clients[index].fd, recv_data);
        }
    }
    return 0;
}
