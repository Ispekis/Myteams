/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscription_cmd
*/

#include "client.h"


static int check_arguments(client_t *client, char **param)
{
    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 1;
    }
    if (param == NULL || param[0] == NULL) {
        printf("Invalid arguments\n");
        return 1;
    }
    return 0;
}

int subscribe_client(client_t *client, char **param)
{
    client_packet packet;

    if (check_arguments(client, param) == 1)
        return 0;
    packet.type = TYPE_SUBSCRIBE;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    uuid_parse(param[0], packet.dest_uuid);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}

int list_subscribed(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }
    packet.type = TYPE_SUBSCRIBED;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    packet.name_len = 0;
    if (!(param == NULL || param[0] == NULL)) {
        uuid_parse(param[0], packet.dest_uuid);
        packet.name_len = 1;
    }
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
}

int unsubscribe_client(client_t *client, char **param)
{
    client_packet packet;

    if (check_arguments(client, param) == 1)
        return 0;
    packet.type = TYPE_UNSUBSCRIBE;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    uuid_parse(param[0], packet.dest_uuid);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
