/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** send
*/

#include "client.h"

int recv_send(client_t *client, server_packet recv_data)
{
    char uuid_str[37];
    char uuid_str2[37];

    uuid_unparse(recv_data.user_uuid, uuid_str);
    uuid_unparse(recv_data.dest_uuid, uuid_str2);
    client_event_private_message_received(uuid_str, recv_data.message);
    return 0;
}
