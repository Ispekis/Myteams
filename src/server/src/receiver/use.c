/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** use
*/

#include "server.h"

static void send_res_team(int client_fd)
{
    server_packet packet;

    packet.type = TYPE_USE;
    packet.code = CODE_200;
    packet.context = DEFAULT_CONTEXT;
    send(client_fd, &packet, sizeof(packet), 0);
}

static void send_res_channel(data_t data, int client_fd,
client_packet recv_data)
{
    server_packet packet;

    packet.type = TYPE_USE;
    if (index_of_team(&data, recv_data) == NULL) {
        packet.code = CODE_404;
    } else {
        packet.code = CODE_200;
        packet.context = CHANNEL_CONTEXT;
        uuid_copy(packet.team_uuid, recv_data.team_uuid);
    }
    send(client_fd, &packet, sizeof(packet), 0);
}

static void send_res_thread(data_t data, int client_fd, client_packet recv_data)
{
    server_packet packet;

    packet.type = TYPE_USE;
    if (index_of_channel(&data, recv_data) == NULL) {
        packet.code = CODE_404;
    } else {
        packet.code = CODE_200;
        packet.context = THREAD_CONTEXT;
        uuid_copy(packet.team_uuid, recv_data.team_uuid);
        uuid_copy(packet.channel_uuid, recv_data.channel_uuid);
    }
    send(client_fd, &packet, sizeof(packet), 0);
}

static void send_res_reply(data_t data, int client_fd, client_packet recv_data)
{
    server_packet packet;

    packet.type = TYPE_USE;
    if (index_of_thread(&data, recv_data) == NULL) {
        packet.code = CODE_404;
    } else {
        packet.code = CODE_200;
        packet.context = REPLY_CONTEXT;
        uuid_copy(packet.team_uuid, recv_data.team_uuid);
        uuid_copy(packet.channel_uuid, recv_data.channel_uuid);
        uuid_copy(packet.thread_uuid, recv_data.thread_uuid);
    }
    send(client_fd, &packet, sizeof(packet), 0);
}

int receive_use(server_t *server, int index, client_packet recv_data)
{
    if (uuid_is_null(recv_data.team_uuid)
        && uuid_is_null(recv_data.channel_uuid)
        && uuid_is_null(recv_data.thread_uuid))
        send_res_team(server->addrs.clients[index].fd);
    if (!uuid_is_null(recv_data.team_uuid)
        && uuid_is_null(recv_data.channel_uuid)
        && uuid_is_null(recv_data.thread_uuid))
        send_res_channel(server->data, server->addrs.clients[index].fd,
        recv_data);
    if (!uuid_is_null(recv_data.team_uuid)
        && !uuid_is_null(recv_data.channel_uuid)
        && uuid_is_null(recv_data.thread_uuid))
        send_res_thread(server->data, server->addrs.clients[index].fd,
        recv_data);
    if (!uuid_is_null(recv_data.team_uuid)
        && !uuid_is_null(recv_data.channel_uuid)
        && !uuid_is_null(recv_data.thread_uuid))
        send_res_reply(server->data, server->addrs.clients[index].fd,
        recv_data);
    return 0;
}
