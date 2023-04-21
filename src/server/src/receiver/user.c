/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** user
*/

#include "server.h"

int receive_users(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    char user_uuid[37];

    uuid_unparse(recv_data.user_uuid, user_uuid);
    data.type = TYPE_USERS;
    uuid_copy(data.user_uuid, recv_data.user_uuid);

    for (int i = 0; i < server->data.nbr_users; i++) {
        uuid_copy(data.dest_uuid, server->data.users[i].uuid);
        strcpy(data.name, server->data.users[i].name);
        data.status = (server->data.users[i].is_logged) ? 1 : 0;
        send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    }
    return 0;
}

int receive_user(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    char dest_user_uuid[37];
    data.type = TYPE_USER;
    uuid_unparse(recv_data.dest_uuid, dest_user_uuid);
    for (int i = 0; i < server->data.nbr_users; i++) {
        if (uuid_compare(server->data.users[i].uuid,
        recv_data.dest_uuid) == 0) {
            data.command_status = SUCCESS;
            uuid_parse(dest_user_uuid, data.dest_uuid);
            strcpy(data.name, server->data.users[i].name);
            data.status = (server->data.users[i].is_logged) ? 1 : 0;
            send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
            return 0;
        }
    }
    data.command_status = FAILURE;
    uuid_parse(dest_user_uuid, data.dest_uuid);
    send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    return 0;
}
