/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create
*/

#include "client.h"

int recv_create(client_t *client, server_packet recv_data)
{
    switch (client->data.context) {
        case DEFAULT_CONTEXT:
            recv_create_team(&client->data, recv_data);
            break;
        case TEAM_CONTEXT:
            break;
        case CHANNEL_CONTEXT:
            break;
        case THREAD_CONTEXT:
            break;
    }
    return 0;
}
