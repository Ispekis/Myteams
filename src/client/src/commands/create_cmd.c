/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_cmd
*/

#include "client.h"

static void choose_create_send(client_packet *packet, data_t data,
char **param)
{
    switch (data.context) {
        case DEFAULT_CONTEXT:
            send_team_packet(packet, data, param);
            break;
        case THREAD_CONTEXT:
            send_thread_packet(packet, data, param);
            break;
        case CHANNEL_CONTEXT:
            break;
        case TEAM_CONTEXT:
            break;
    }
}

int create_sub_res(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }
    if (param == NULL || param[0] == NULL || param[1] == NULL) {
        printf("Invalid arguments\n");
        return 0;
    }
    packet.type = TYPE_CREATE;
    packet.context = client->data.context;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    choose_create_send(&packet, client->data, param);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
