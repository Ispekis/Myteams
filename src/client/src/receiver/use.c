/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** use
*/

#include "client.h"

int recv_use(client_t *client, server_packet recv_data)
{
    client->data.context = recv_data.context;
    printf("%d\n", client->data.context);
    return 0;
}
