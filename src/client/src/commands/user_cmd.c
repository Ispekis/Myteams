/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** user_commands
*/

#include "client.h"

int get_users(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }

    packet.type = TYPE_USERS;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}

int get_user(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }

    if (param == NULL) {
        printf("Invalid argument\n");
        return 0;
    }

    packet.type = TYPE_USER;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    strcpy(packet.name, client->data.user_name);
    uuid_parse(param[0], packet.dest_uuid);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
