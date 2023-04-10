/*
** EPITECH PROJECT, 2023
** commands_handler
** File description:
** commands_handler
*/

#include "client.h"

int user_login(client_t *client, char **param)
{
    dprintf(client->addrs.server_fd, "used loging cmd");
    return 0;
}

int user_logout(client_t *client, char **param)
{
    dprintf(client->addrs.server_fd, "used logout cmd");
    return 0;
}
