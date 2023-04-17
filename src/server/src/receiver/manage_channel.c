/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** manage_channel
*/

#include "server.h"

int create_channel(server_t *server, char *name)
{
    channel_t* new_channel = realloc(server->data.channel,
    (server->data.nbr_channel + 1) * sizeof(channel_t));
    if (new_channel == NULL)
        return 1;

    server->data.channel = new_channel;
    server->data.channel[server->data.nbr_channel].name =
    malloc(sizeof(char) * (strlen(name) + 1));
    if (server->data.channel[server->data.nbr_channel].name == NULL)
        return 1;
    strcpy(server->data.channel[server->data.nbr_channel].name, name);
    uuid_generate(server->data.channel[server->data.nbr_channel].uuid);
    server->data.channel++;
    return 0;
}

int receive_channel(server_t *server, int index, client_packet recv_data)
{
    char uuid_str[37];

    for (int i = 0; i < server->data.nbr_channel; ++i) {
    }
    create_channel(server, recv_data.);
}