/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribed_users
*/

#include "server.h"

static int get_status(bool logged)
{
    if (logged)
        return 1;
    return 0;
}

static void send_responses(data_t data, teams_t team, int i, int client_fd)
{
    server_packet list_packet;

    for (int y = 0; y < data.nbr_users; y++) {
        if (uuid_compare(team.members_uuid[i],
            data.users[y].uuid) == 0) {
            uuid_copy(list_packet.user_uuid, data.users[y].uuid);
            strcpy(list_packet.name, data.users[y].name);
            list_packet.status = get_status(data.users[y].is_logged);
            send(client_fd, &list_packet, sizeof(list_packet), 0);
        }
    }
}

void list_subscribed_user(data_t data, teams_t team, int client_fd)
{
    server_packet packet;

    packet.type = TYPE_SUBSCRIBED;
    packet.context = CHANNEL_CONTEXT;
    packet.nbr = team.subs_nbr;
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < team.subs_nbr; i++) {
        send_responses(data, team, i, client_fd);
    }
}
