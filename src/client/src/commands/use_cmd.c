/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** use_cmd
*/

#include "client.h"

static void clear_uuids(client_packet *packet)
{
    uuid_clear(packet->team_uuid);
    uuid_clear(packet->channel_uuid);
    uuid_clear(packet->thread_uuid);
}

int use_command(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        print_code_res(CODE_403);
        client_error_unauthorized();
        return 0;
    }
    clear_uuids(&packet);
    if (param != NULL) {
        if (param[0] != NULL)
            uuid_parse(param[0], packet.team_uuid);
        if (param[1] != NULL)
            uuid_parse(param[1], packet.channel_uuid);
        if (param[2] != NULL)
            uuid_parse(param[2], packet.thread_uuid);
    }
    packet.type = TYPE_USE;
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
