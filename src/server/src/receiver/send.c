/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** communication_cmd
*/

#include "server.h"

int receive_send(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    char uuid_str[37];
    char uuid_str2[37];

    uuid_unparse(recv_data.user_uuid, uuid_str);
    uuid_unparse(recv_data.dest_uuid, uuid_str2);
    server_event_private_message_sended(uuid_str, uuid_str2, recv_data.message);
    data.type = TYPE_SEND;
    uuid_copy(data.user_uuid, recv_data.user_uuid);
    strcpy(data.name, recv_data.name);
    strcpy(data.message, recv_data.message);
    data.message_len = recv_data.message_len;
    uuid_copy(data.dest_uuid, recv_data.dest_uuid);
    for (int i = 0; i < server->data.nbr_users; i++)
        if (uuid_compare(server->data.users[i].uuid, recv_data.dest_uuid) == 0)
            send(server->data.users[i].current_fd, &data, sizeof(data), 0);

    return 0;
}
