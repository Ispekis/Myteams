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
    char *msg = "msg1";

    packet.type = TYPE_MESSAGES;
    packet.nbr_messages = get_nbr_corresponding_msg(client_fd, user,
    dest_uuid);
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < user.nbr_messages; i++) {
        if ((uuid_compare(user.messages->sender_uuid, user.uuid) == 0
        && uuid_compare(user.messages->dest_uuid, dest_uuid) == 0)
        || (uuid_compare(user.messages->dest_uuid, user.uuid) == 0
        && uuid_compare(user.messages->sender_uuid, dest_uuid) == 0)) {
            // send(client_fd, &msg, (sizeof(msg) * strlen(msg)), 0);
            printf("%s\n", user.messages[i].message);
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