/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** init
*/

#include "client.h"

static int create_socket_client(sock_addrs_t *addrs, char *ip, int port)
{
    addrs->client.sin_family = AF_INET;
    addrs->client.sin_port = htons(port);
    addrs->client.sin_addr.s_addr = inet_addr(ip);
    addrs->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (addrs->server_fd < 0)
        return 1;
    addrs->status = connect(addrs->server_fd, (const struct sockaddr *)
    &addrs->client, sizeof(addrs->client));
    if (addrs->status < 0)
        return 1;
    printf("Connected to server\n");
    return 0;
}

static void init_commands(client_t *client)
{
    client->cmd[HELP] = show_help;
    client->cmd[LOGIN] = user_login;
    client->cmd[LOGOUT] = user_logout;
    client->cmd[USERS] = get_users;
    client->cmd[USER] = get_user;
    client->cmd[SEND] = send_message;
    client->cmd[MESSAGES] = list_messages;
    client->cmd[SUBSCRIBE] = subscribe_client;
    client->cmd[SUBSCRIBED] = list_subscribed;
    client->cmd[UNSUBSCRIBE] = unsubscribe_client;
    client->cmd[USE] = set_command;
    client->cmd[CREATE] = create_sub_res;
    client->cmd[LIST] = list_sub_res;
    client->cmd[INFO] = info_current_res;
}

int init_client(client_t *client, char *ip, int port)
{
    if (create_socket_client(&client->addrs, ip, port) == 1)
        return 1;
    init_commands(client);
    return 0;
}