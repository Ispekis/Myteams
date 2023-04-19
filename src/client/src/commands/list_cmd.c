/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** list_cmd
*/

#include "client.h"

int list_sub_res(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }

    return 0;
}

int list_all_teams(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }

    packet.type = TYPE_LIST;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
