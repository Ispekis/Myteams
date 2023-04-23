/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** communication_cmd
*/

#include "client.h"

int send_message(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        client_error_unauthorized();
        return 0;
    }
    if (param == NULL || (param[0] != NULL && param[1] == NULL)) {
        printf("Invalid arguments\n");
        return 0;
    }
    packet.type = TYPE_SEND;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    strcpy(packet.name, client->data.user_name);
    strcpy(packet.message, param[1]);
    packet.message_len = strlen(param[1]) + 1;
    uuid_parse(param[0], packet.dest_uuid);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}

int list_messages(client_t *client, char **param)
{
    client_packet packet;

    if (param == NULL)
        return 1;

    packet.type = TYPE_MESSAGES;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    uuid_parse(param[0], packet.dest_uuid);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
