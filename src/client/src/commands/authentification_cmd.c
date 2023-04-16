/*
** EPITECH PROJECT, 2023
** commands_handler
** File description:
** commands_handler
*/

#include "client.h"

typedef struct {
    int type;
    char *name;
    int name_len;
} client_packet;

int user_login(client_t *client, char **param)
{
    client_packet packet;

    packet.type = TYPE_LOGIN;
    packet.name = param[0];
    packet.name_len = strlen(packet.name) + 1;
    send(client->addrs.server_fd, &packet.type, sizeof(packet.type), 0);
    send(client->addrs.server_fd, &packet.name_len, sizeof(packet.name_len), 0);
    send(client->addrs.server_fd, packet.name, packet.name_len, 0);
    return 0;
}

int user_logout(client_t *client, char **param)
{
    dprintf(client->addrs.server_fd, "used logout cmd");
    return 0;
}
