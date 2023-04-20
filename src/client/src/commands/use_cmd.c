/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** use_cmd
*/

#include "client.h"

int use_command(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }

    if (param == NULL)
        uuid_clear(packet.dest_uuid);
    else
        uuid_parse(param[0], packet.dest_uuid);

    packet.type = TYPE_USE;
    packet.context = client->data.context;
    printf("%d\n", client->data.context);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
