/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** user
*/

#include "client.h"

int recv_user(client_t *client, server_packet recv_data)
{
    char dest_uuid[37];

    uuid_unparse(recv_data.dest_uuid, dest_uuid);
    client_print_user(dest_uuid, recv_data.name, recv_data.status);
    return 0;
}

int recv_users(client_t *client, server_packet recv_data)
{
    char dest_uuid[37];

    uuid_unparse(recv_data.dest_uuid, dest_uuid);
    client_print_users(dest_uuid, recv_data.name, recv_data.status);
    return 0;
}
