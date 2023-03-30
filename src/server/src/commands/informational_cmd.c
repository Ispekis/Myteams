/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myftp-vincent.shao
** File description:
** informational_cmd
*/

#include "server.h"

int show_help(server_t *server, char **params, int index)
{
    reply_format(server->addrs.clients[index].fd, C214);
    return 0;
}

int get_users(server_t *server, char **params, int index)
{
    return 0;
}

int get_user(server_t *server, char **params, int index)
{
    return 0;
}
