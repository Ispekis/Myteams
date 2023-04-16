/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** logout
*/

#include "client.h"

int recv_logout(client_t *client, server_packet recv_data)
{
    char uuid_str[37];

    uuid_unparse(recv_data.user_uuid, uuid_str);
    client_event_logged_out(uuid_str, recv_data.user_name);
    return 0;
}