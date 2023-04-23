/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** list_cmd
*/

#include "client.h"


static void choose_send(client_packet *packet, data_t data)
{
    switch (packet->context) {
        case DEFAULT_CONTEXT:
            send_list_team(packet, data);
            break;
        case CHANNEL_CONTEXT:
            send_list_channel(packet, data);
            break;
        case THREAD_CONTEXT:
            send_list_thread(packet, data);
            break;
        case REPLY_CONTEXT:
            send_list_reply(packet, data);
            break;
    }
}

int list_sub_res(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        client_error_unauthorized();
        return 0;
    }
    packet.type = TYPE_LIST;
    packet.context = client->data.context;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    choose_send(&packet, client->data);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
