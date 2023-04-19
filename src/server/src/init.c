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

static void init_receiver(server_t *server)
{
    server->receive[TYPE_LOGIN] = receive_login;
    server->receive[TYPE_LOGOUT] = receive_logout;
    server->receive[TYPE_SEND] = receive_send;
    server->receive[TYPE_USER] = receive_user;
    server->receive[TYPE_USERS] = receive_users;
    server->receive[TYPE_CREATE_TEAM] = receive_teams;
    server->receive[TYPE_SUBSCRIBE] = receive_subscribe;
    server->receive[TYPE_LIST] = receive_list_teams;
    server->receive[TYPE_UNSUBSCRIBE] = receive_unsubscribe;
    server->receive[TYPE_USE] = receive_use;
}

static void init_data(server_t *server)
{
    server->data.nbr_users = 0;
    server->data.users = malloc(sizeof(user_t));
    server->data.nbr_teams = 0;
    server->data.teams = malloc(sizeof(teams_t));
}

int init_server(server_t *server, int port)
{
    if (create_socket_server(&server->addrs, port) == 1)
        return 1;
    init_receiver(server);
    init_data(server);
    return 0;
}
