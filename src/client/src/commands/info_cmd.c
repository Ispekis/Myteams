/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** info_cmd
*/

#include "client.h"

static int choose_info_send(client_packet *packet, data_t data)
{
    switch (data.context) {
        case DEFAULT_CONTEXT:
            do_default_info(data);
            return 1;
        case THREAD_CONTEXT:
            send_info_channel(packet, data);
            return 0;
        case CHANNEL_CONTEXT:
            send_info_team(packet, data);
            return 0;
        case REPLY_CONTEXT:
            send_info_thread(packet, data);
            return 0;
    }
    return 0;
}

int info_current_res(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        print_code_res(CODE_403);
        client_error_unauthorized();
        return 0;
    }
    packet.type = TYPE_INFO;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    packet.context = client->data.context;
    if (choose_info_send(&packet, client->data) == 1)
        return 0;
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
