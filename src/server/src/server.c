/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** server
*/

#include "server.h"

void re_set_fds(sock_addrs_t *addrs)
{
    FD_ZERO(&addrs->rfds);
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (addrs->clients[i].fd >= 0) {
            FD_SET(addrs->clients[i].fd, &addrs->rfds);
        }
    }
}

static int listen_events(server_t *server)
{
    if (FD_ISSET(server->addrs.socket_fd, &server->addrs.rfds)) {
        accept_client_to_server(&server->addrs);
    }
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        read_from_client(server, i);
    }
    return 0;
}

int run_server(int port)
{
    server_t server;

    if (init_server(&server, port) == 1)
        return 1;
    while (1) {
        re_set_fds(&server.addrs);
        if (select(FD_SETSIZE, &server.addrs.rfds, NULL, NULL, NULL) < 0)
            return 1;
        listen_events(&server);
    }
    return 0;
}
