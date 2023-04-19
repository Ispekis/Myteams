/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** messages
*/

#include "server.h"

static int get_nbr_corresponding_msg(int client_fd, user_t user,
uuid_t dest_uuid)
{
    int count = 0;

    for (int i = 0; i < user.nbr_messages; i++) {
        if ((uuid_compare(user.messages->sender_uuid, user.uuid) == 0
        && uuid_compare(user.messages->dest_uuid, dest_uuid) == 0)
        || (uuid_compare(user.messages->dest_uuid, user.uuid) == 0
        && uuid_compare(user.messages->sender_uuid, dest_uuid) == 0)) {
            count++;
        }
    }
    return count;
}

static int check_messages(int client_fd, user_t user, uuid_t dest_uuid)
{
    server_packet packet;
    char uuid_str[MAX_UUID_LENGTH];
    uint32_t timestamp;

    packet.type = TYPE_MESSAGES;
    packet.nbr_messages = get_nbr_corresponding_msg(client_fd, user,
    dest_uuid);
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < user.nbr_messages; i++) {
        if ((uuid_compare(user.messages->sender_uuid, user.uuid) == 0
        && uuid_compare(user.messages->dest_uuid, dest_uuid) == 0)
        || (uuid_compare(user.messages->dest_uuid, user.uuid) == 0
        && uuid_compare(user.messages->sender_uuid, dest_uuid) == 0)) {
            uuid_unparse(user.messages->sender_uuid, uuid_str);
            timestamp = htonl(user.messages[i].timestamp);
            send(client_fd, &timestamp, sizeof(timestamp), 0);
            send(client_fd, uuid_str, MAX_UUID_LENGTH, 0);
            send(client_fd, user.messages[i].message, strlen(user.messages[i].message), 0);
        }
    }
}

int receive_messages(server_t *server, int index, client_packet recv_data)
{
    for (int i = 0; i < server->data.nbr_users; i++) {
        if (uuid_compare(recv_data.user_uuid, server->data.users[i].uuid) == 0) {
            check_messages(server->addrs.clients[index].fd,
            server->data.users[i], recv_data.dest_uuid);
        }
    }
    return 0;
}