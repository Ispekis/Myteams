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
} login_packet;

int user_login(client_t *client, char **param)
{
    login_packet lp;

    lp.name = param[0];
    client_event_logged_in("ok", "ok");
    lp.type = LOGIN;
    send(client->addrs.server_fd, &lp.type, sizeof(lp.type), 0);
    lp.name_len = strlen(lp.name) + 1;
    send(client->addrs.server_fd, &lp.name_len, sizeof(lp.name_len), 0);
    send(client->addrs.server_fd, lp.name, lp.name_len, 0);
    return 0;
}

int user_logout(client_t *client, char **param)
{
    dprintf(client->addrs.server_fd, "used logout cmd");
    return 0;
}
