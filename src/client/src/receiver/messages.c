/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** messages
*/

#include "client.h"

int recv_messages(client_t *client, server_packet recv_data)
{
    char message[MAX_MESSAGE_LENGTH];
    char sender_uuid[MAX_UUID_LENGTH];
    uint32_t timestamp;
    time_t recv_time;

    for (int i = 0; i < recv_data.nbr_messages; i++) {
        recv(client->addrs.server_fd, &timestamp, sizeof(timestamp), 0);
        recv(client->addrs.server_fd, sender_uuid, MAX_UUID_LENGTH, 0);
        recv(client->addrs.server_fd, message, MAX_MESSAGE_LENGTH, 0);
        recv_time = ntohl(timestamp);
        client_private_message_print_messages(sender_uuid, recv_time, message);
    }
    return 0;
}
