/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** read_server
*/

#include "client.h"

void read_server(client_t *client)
{
    server_packet recv_data;
    if (FD_ISSET(client->addrs.server_fd, &client->addrs.rfds)) {
        recv(client->addrs.server_fd, &recv_data, sizeof(recv_data), 0);
        printf("%i\n", recv_data.user_name_len);
    }
}
