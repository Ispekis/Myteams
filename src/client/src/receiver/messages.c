/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** messages
*/

#include "client.h"

int recv_messages(client_t *client, server_packet recv_data)
{
    for (int i = 0; i < recv_data.nbr_messages; i++) {
        // recv(client->addrs.server_fd, message, 4, 0);
        printf("%s\n", "msg");
    }
    return 0;
}
