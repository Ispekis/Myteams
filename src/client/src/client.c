/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** client
*/

#include "client.h"

static void re_setfds(client_t *client)
{
    FD_ZERO(&client->addrs.rfds);
    FD_ZERO(&client->addrs.wfds);
    FD_ZERO(&client->addrs.efds);
    FD_SET(STDIN_FILENO, &client->addrs.rfds);
    FD_SET(client->addrs.server_fd, &client->addrs.rfds);
}

void destructor(client_t *client)
{
}

int run_client(char *ip, int port)
{
    client_t client;

    if (init_client(&client, ip, port) == 1)
        return 1;
    while (true) {
        re_setfds(&client);
        if (select(FD_SETSIZE, &client.addrs.rfds, &client.addrs.wfds,
        &client.addrs.efds, NULL) < 0)
            return 1;
        read_client_cli(&client);
        read_server(&client);
    }
    destructor(&client);
    return 0;
}
