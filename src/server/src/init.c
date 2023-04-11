/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** init
*/

#include "server.h"

static void init_client(client_t *client)
{
    client->fd = -1;
}

static int create_socket_server(sock_addrs_t *addrs, int port)
{
    addrs->server.sin_family = AF_INET;
    addrs->server.sin_port = htons(port);
    addrs->server.sin_addr.s_addr = INADDR_ANY;
    addrs->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (addrs->socket_fd < 0)
        return 1;
    addrs->name = bind(addrs->socket_fd,
    (const struct sockaddr *) &addrs->server, sizeof(addrs->server));
    if (addrs->name < 0)
        return 1;
    addrs->status = listen(addrs->socket_fd, MAX_CONNECTIONS);
    if (addrs->status < 0)
        return 1;
    for (int i = 0; i < MAX_CONNECTIONS; i++)
        init_client(&addrs->clients[i]);
    addrs->clients[0].fd = addrs->socket_fd;
    FD_ZERO(&addrs->rfds);
    return 0;
}

int init_server(server_t *server, int port)
{
    if (create_socket_server(&server->addrs, port) == 1)
        return 1;
    server->handle = dlopen("libs/myteams/libmyteams.so", RTLD_LAZY);
    if (!server->handle)
        return 1;
    return 0;
}
