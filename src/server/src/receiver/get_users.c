/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** get_users
*/

#include "server.h"

static void send_response(int client_fd, user_t user)
{

}

static void get_users(user_t *user)
{
    char uuid_str[37];

    uuid_unparse(user->uuid, uuid_str);
    client_print_users(uuid_str, user->name, user->is_logged);
}

int receive_users(server_t *server, int index, client_packet recv_data)
{
    return 0;
}