/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myftp-vincent.shao
** File description:
** client_management
*/

#include "server.h"

typedef struct {
    int type;
    char *name;
    int name_len;
} login_packet;

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

void login_client(server_t *server, int index)
{
    login_packet data;

    recv(server->addrs.clients[index].fd, &data.name_len, sizeof(data.name_len), 0);
    char* name = malloc(data.name_len);
    recv(server->addrs.clients[index].fd, name, data.name_len, 0);
    data.name = name;
    printf("data = %s\n", data.name);
}

void read_from_client(server_t *server, int index)
{
    char buffer[1024];
    size_t bytes = 0;
    login_packet data;

    if (FD_ISSET(server->addrs.clients[index].fd, &server->addrs.rfds)) {
        if (server->addrs.clients[index].fd >= 0 &&
        server->addrs.clients[index].fd != server->addrs.socket_fd) {
            int type;
            recv(server->addrs.clients[index].fd, &type, sizeof(type), 0);
            printf("type = %i\n", type);
            login_client(server, index);
            // recv(server->addrs.clients[index].fd, &data.name_len, sizeof(data.name_len), 0);
            // char* name = malloc(data.name_len);
            // recv(server->addrs.clients[index].fd, name, data.name_len, 0);
            // data.name = name;
            // printf("data = %s\n", data.name);
            // bytes = recv(server->addrs.clients[index].fd, &dl, sizeof(dl), 0);
            // do_remove_client(bytes, &server->addrs.clients[index]);
            // memset(buffer, '\0', sizeof(buffer));
        }
    }
}
