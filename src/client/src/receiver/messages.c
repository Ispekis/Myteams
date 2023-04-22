/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** messages
*/

#include "client.h"

int recv_messages(client_t *client, server_packet recv_data)
{
    server_packet msg_packet;
    char sender_uuid[MAX_UUID_LENGTH];

    for (int i = 0; i < recv_data.nbr_messages; i++) {
        recv(client->addrs.server_fd, &msg_packet, sizeof(msg_packet), 0);
        uuid_unparse(msg_packet.send_uuid, sender_uuid);
        client_private_message_print_messages(sender_uuid,
        msg_packet.timestamp, msg_packet.message);
    }
    return 0;
}
