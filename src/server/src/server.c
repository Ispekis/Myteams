/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** server
*/

#include "server.h"

void re_set_fds(sock_addrs_t *addrs, int sfd)
{
    FD_ZERO(&addrs->rfds);
    FD_SET(sfd, &addrs->rfds);
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

static void destructor(server_t *server)
{
}

int block_signal(int *sfd)
{
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
        return 1;
    *sfd = signalfd(-1, &mask, 0);
    if (*sfd == -1)
        return 1;
    return 0;
}

int run_server(int port)
{
    server_t server;

    if (init_server(&server, port) == 1)
        return 1;
    block_signal(&server.sfd);
    while (true) {
        re_set_fds(&server.addrs, server.sfd);
        if (select(FD_SETSIZE, &server.addrs.rfds, NULL, NULL, NULL) < 0)
            return 1;
        if (catch_shutdown(server) == 1)
            break;
        listen_events(&server);
    }
    destructor(&server);
    return 0;
}
