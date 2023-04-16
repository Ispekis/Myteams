/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** read_server
*/

#include "client.h"

int read_server(client_t *client)
{
    server_packet recv_data;
    int bytes;

    if (FD_ISSET(client->addrs.server_fd, &client->addrs.rfds)) {
        bytes = recv(client->addrs.server_fd, &recv_data, sizeof(recv_data), 0);
        if (bytes > 0)
            client->receive[recv_data.type](client, recv_data);
        if (bytes == 0) {
            printf("Server closed\n");
            return 1;
        }
    }
    return 0;
}
