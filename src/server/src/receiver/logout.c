/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** logout
*/

#include "server.h"

static void send_response(int client_fd, user_t user)
{
    server_packet packet;

    packet.type = TYPE_LOGOUT;
    uuid_copy(packet.user_uuid, user.uuid);
    strcpy(packet.user_name, user.name);
    send(client_fd, &packet, sizeof(packet), 0);
}

static void logout_user(user_t *user)
{
    char uuid_str[37];

    uuid_unparse(user->uuid, uuid_str);
    server_event_user_logged_out(uuid_str);
    user->is_logged = false;
    user->current_fd = -1;
}

int receive_logout(server_t *server, int index, client_packet recv_data)
{
    for (int i = 0; i < server->data.nbr_users; i++) {
        if (uuid_compare(server->data.users[i].uuid,
        recv_data.user_uuid) == 0) {
            logout_user(&server->data.users[i]);
            send_response(server->addrs.clients[index].fd,
            server->data.users[i]);
        }
    }
    return 0;
}
