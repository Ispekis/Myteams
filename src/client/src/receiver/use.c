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
    uuid_copy(client->data.context_type.team_uuid, recv_data.team_uuid);
    return 0;
}
