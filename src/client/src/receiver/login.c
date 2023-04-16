/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** login
*/

#include "client.h"

int recv_login(client_t *client, server_packet recv_data)
{
    client_event_logged_in(recv_data.user_uuid, recv_data.user_name);
    client->data.is_logged = true;
    return 0;
}
