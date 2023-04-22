/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_cmd
*/

#include "client.h"

static int choose_create_send(client_packet *packet, data_t data,
char **param)
{
    switch (data.context) {
        case DEFAULT_CONTEXT:
            return send_team_packet(packet, data, param);
        case THREAD_CONTEXT:
            return send_thread_packet(packet, data, param);
        case CHANNEL_CONTEXT:
            return send_channel_packet(packet, data, param);
        case REPLY_CONTEXT:
            return send_reply_packet(packet, data, param);
    }
}

int create_sub_res(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        print_code_res(CODE_403);
        return 0;
    }
    if (param == NULL) {
        print_code_res(CODE_400);
        return 0;
    }
    packet.type = TYPE_CREATE;
    packet.context = client->data.context;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    if (choose_create_send(&packet, client->data, param) == 1) {
        print_code_res(CODE_400);
        return 0;
    }
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
