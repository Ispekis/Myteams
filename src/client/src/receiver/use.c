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
    if (recv_data.context == REPLY_CONTEXT)
        uuid_copy(client->data.context_type.team_uuid, recv_data.use_uuid);
    if (recv_data.context == CHANNEL_CONTEXT)
        uuid_copy(client->data.context_type.channel_uuid, recv_data.use_uuid);
    if (recv_data.context == THREAD_CONTEXT)
        uuid_copy(client->data.context_type.thread_uuid, recv_data.use_uuid);
    return 0;
}
