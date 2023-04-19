/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** messages
*/

#include "server.h"

static int check_messages(user_t user, uuid_t dest_uuid)
{
    for (int i = 0; i < user.nbr_messages; i++) {
        if ((uuid_compare(user.messages->sender_uuid, user.uuid) == 0
        && uuid_compare(user.messages->dest_uuid, dest_uuid) == 0)
        || (uuid_compare(user.messages->dest_uuid, user.uuid) == 0
        && uuid_compare(user.messages->sender_uuid, dest_uuid) == 0)) {
            printf("%s\n", user.messages[i].message);
        }
    }
}

int receive_messages(server_t *server, int index, client_packet recv_data)
{
    for (int i = 0; i < server->data.nbr_users; i++) {
        if (uuid_compare(recv_data.user_uuid, server->data.users[i].uuid) == 0) {
            check_messages(server->data.users[i], recv_data.dest_uuid);
        }
    }
    return 0;
}