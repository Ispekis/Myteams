/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribed
*/

#include "client.h"

static void recv_subscribed_teams(client_t *client, server_packet recv_data)
{
    server_packet packet;
    char uuid_str[MAX_UUID_LENGTH];

    for (int i = 0; i < recv_data.nbr; i++) {
        recv(client->addrs.server_fd, &packet, sizeof(packet), 0);
        uuid_unparse(packet.team_uuid, uuid_str);
        client_print_teams(uuid_str, packet.team_name, packet.description);
    }
}

static void recv_subscribed_users(client_t *client, server_packet recv_data)
{
    server_packet packet;
    char uuid_str[MAX_UUID_LENGTH];

    for (int i = 0; i < recv_data.nbr; i++) {
        recv(client->addrs.server_fd, &packet, sizeof(packet), 0);
        uuid_unparse(packet.user_uuid, uuid_str);
        client_print_users(uuid_str, packet.name, packet.status);
    }
}

int recv_subscribed(client_t *client, server_packet recv_data)
{
    char tmp_uuid[MAX_UUID_LENGTH];

    if (recv_data.context == DEFAULT_CONTEXT) {
        recv_subscribed_teams(client, recv_data);
    } else {
        if (recv_data.code.code == CODE_200.code) {
            recv_subscribed_users(client, recv_data);
        } else {
            uuid_unparse(recv_data.team_uuid, tmp_uuid);
            client_error_unknown_team(tmp_uuid);
        }
    }
    return 0;
}
