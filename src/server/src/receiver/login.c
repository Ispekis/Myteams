/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** login
*/

#include "server.h"

int create_user(server_t *server, int index, char* name)
{
    user_t* new_user = realloc(server->data.users,
    (server->data.nbr_users + 1) * sizeof(user_t));
    if (new_user == NULL)
        return 1;

    server->data.users = new_user;
    server->data.users[server->data.nbr_users].name =
    malloc(sizeof(char) * (strlen(name) + 1));
    if (server->data.users[server->data.nbr_users].name == NULL)
        return 1;
    strcpy(server->data.users[server->data.nbr_users].name, name);
    uuid_generate(server->data.users[server->data.nbr_users].uuid);
    server->data.users[server->data.nbr_users].subbed_teams =
    malloc(sizeof(char *) + 1);
    server->data.users[server->data.nbr_users].subbed_teams[0] = NULL;
    server->data.users[server->data.nbr_users].nbr_teams = 0;
    server->data.nbr_users++;
    return 0;
}

static int send_response(int client_fd, char *name, char *uuid, code_t code)
{
    server_packet data;

    data.type = TYPE_LOGIN;
    data.code = code;
    if (code.code == CODE_200.code) {
        server_event_user_logged_in(uuid);
        data.user_name_len = strlen(name) + 1;
        data.context = DEFAULT_CONTEXT;
        strcpy(data.name, name);
        data.user_uuid, uuid_parse(uuid, data.user_uuid);
    }
    send(client_fd, &data, sizeof(data), 0);
    return 0;
}

static void connect_user(user_t *user, int fd)
{
    user->is_logged = true;
    user->current_fd = fd;
    user->context = DEFAULT_CONTEXT;
    user->nbr_messages = 0;
    user->messages = malloc(sizeof(messages_t));
}

code_t verify_loggin(user_t user)
{
    if (user.is_logged)
        return CODE_400;
    return CODE_200;
}

int receive_login(server_t *server, int index, client_packet recv_data)
{
    char uuid_str[37];

    for (int i = 0; i < server->data.nbr_users; i++)
        if (strcmp(server->data.users[i].name, recv_data.name) == 0) {
            uuid_unparse(server->data.users[i].uuid, uuid_str);
            send_response(server->addrs.clients[index].fd, server->data.
            users[i].name, uuid_str, verify_loggin(server->data.users[i]));
            connect_user(&server->data.users[i],
            server->addrs.clients[index].fd);
            return 0;
        }
    create_user(server, index, recv_data.name);
    connect_user(&server->data.users[server->data.nbr_users - 1],
    server->addrs.clients[index].fd);
    uuid_unparse(server->data.users[server->data.nbr_users - 1].uuid,
    uuid_str);
    send_response(server->addrs.clients[index].fd,
    server->data.users[server->data.nbr_users - 1].name, uuid_str, CODE_200);
    return 0;
}
