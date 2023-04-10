/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myftp-vincent.shao
** File description:
** client_management
*/

#include "server.h"

static void add_client(client_t *clients, int client_fd)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (clients[i].fd < 0) {
            clients[i].fd = client_fd;
            break;
        }
    }
}

void accept_client_to_server(sock_addrs_t *addrs)
{
    struct sockaddr_in client;
    int len = sizeof(client);
    int client_fd = accept(addrs->socket_fd,
    (struct sockaddr *) &client,  &len);

    if (client_fd >= 0) {
        printf("Connection from %s:%d\n", inet_ntoa(client.sin_addr),
        client.sin_port);
        add_client(addrs->clients, client_fd);
    }
}

static void do_remove_client(int bytes, client_t *client)
{
    if (bytes == -1) {
        client->fd = -1;
    }
}

void read_from_client(server_t *server, int index)
{
    char buffer[1024];
    size_t bytes = 0;

    if (FD_ISSET(server->addrs.clients[index].fd, &server->addrs.rfds)) {
        if (server->addrs.clients[index].fd >= 0 &&
        server->addrs.clients[index].fd != server->addrs.socket_fd) {
            bytes = read(server->addrs.clients[index].fd, buffer, 1024);
            printf("%s\n", buffer);
            do_remove_client(bytes, &server->addrs.clients[index]);
            memset(buffer, '\0', sizeof(buffer));
        }
    }
}