/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** info_cmd
*/

#include "client.h"

void do_default_info(client_t *client)
{
    char uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(client->data.user_uuid, uuid_str);
    client_print_user(uuid_str, client->data.user_name,
    client->data.is_logged);
}

int info_current_res(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }
    if (client->data.context == DEFAULT_CONTEXT) {
        do_default_info(client);
        return 0;
    }
    packet.type = TYPE_INFO;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    packet.context = client->data.context;
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
