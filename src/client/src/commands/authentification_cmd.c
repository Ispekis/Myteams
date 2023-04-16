/*
** EPITECH PROJECT, 2023
** commands_handler
** File description:
** commands_handler
*/

#include "client.h"

int user_login(client_t *client, char **param)
{
    client_packet packet;

    if (param[0] == NULL)
        return 0;
    if (client->data.is_logged) {
        printf("Already logged\n");
        return 0;
    }
    packet.type = TYPE_LOGIN;
    strcpy(packet.user_name, param[0]);
    packet.name_len = strlen(param[0]) + 1;
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}

int user_logout(client_t *client, char **param)
{
    dprintf(client->addrs.server_fd, "used logout cmd");
    return 0;
}
