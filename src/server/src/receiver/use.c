/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** use
*/

#include "server.h"

static int send_teams(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    data.type = TYPE_USE;
    data.context = TEAM_CONTEXT;
    uuid_copy(data.team_uuid, recv_data.use_uuid);
    send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    return 0;
}

static int send_channel(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    data.type = TYPE_USE;
    data.context = CHANNEL_CONTEXT;
    uuid_copy(data.channel_uuid, recv_data.use_uuid);
    send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    return 0;
}

static int send_thread(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    data.type = TYPE_USE;
    data.context = THREAD_CONTEXT;
    uuid_copy(data.thread_uuid, recv_data.use_uuid);
    send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    return 0;
}

static int send_response(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    data.type = TYPE_USE;
    for (int i = 0; i < server->data.nbr_teams; i++)
        if (uuid_compare(server->data.teams[i].teams_uuid,
        recv_data.use_uuid) == 0)
            return send_teams(server, index, recv_data);
    for (int i = 0; i < server->data.nbr_channel; i++)
        if (uuid_compare(server->data.channel[i].uuid,
        recv_data.use_uuid) == 0)
            return send_channel(server, index, recv_data);
    for (int i = 0; i < server->data.nbr_thread; i++)
        if (uuid_compare(server->data.threads[i].thread_uuid,
        recv_data.use_uuid) == 0)
            return send_thread(server, index, recv_data);

    data.context = recv_data.context;
    uuid_copy(data.team_uuid, recv_data.use_uuid);
    send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    return 0;
}

int receive_use(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    char team_uuid[37];
    data.type = TYPE_USE;

    uuid_unparse(recv_data.use_uuid, team_uuid);
    if (uuid_is_null(recv_data.use_uuid)) {
        data.context = DEFAULT_CONTEXT;
        uuid_copy(data.send_uuid, recv_data.use_uuid);
        send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    } else {
        send_response(server, index, recv_data);
    }
    return 0;
}
