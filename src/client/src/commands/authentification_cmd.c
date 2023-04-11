/*
** EPITECH PROJECT, 2023
** commands_handler
** File description:
** commands_handler
*/

#include "client.h"

int user_login(client_t *client, char **param)
{
    int (*client_event_logged_in)(char const *, const char *);
    client_event_logged_in = dlsym(client->handle, "client_event_logged_in");

    dprintf(client->addrs.server_fd, "used loging cmd");
    return 0;
}

int user_logout(client_t *client, char **param)
{
    int (*client_event_logged_out)(char const *, const char *);
    client_event_logged_out = dlsym(client->handle, "client_event_logged_out");

    dprintf(client->addrs.server_fd, "used logout cmd");
    return 0;
}
