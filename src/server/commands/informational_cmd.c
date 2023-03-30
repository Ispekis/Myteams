/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myftp-vincent.shao
** File description:
** informational_cmd
*/

#include "server.h"

int show_help(server_t *server, char **params, int index)
{
    printf("help");
    // if (!server->addrs.connections[index].is_logged) {
    //     reply_format(server->addrs.connections[index].fd, CODE_530);
    //     return 0;
    // }
    // reply_format(server->addrs.connections[index].fd, CODE_214);
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
