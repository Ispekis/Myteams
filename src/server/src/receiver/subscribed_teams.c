/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribed_teams
*/

#include "server.h"

static void send_responses(data_t data, user_t user, int i, int client_fd)
{
    server_packet list_packet;

    for (int y = 0; y < data.nbr_teams; y++) {
        if (uuid_compare(user.teams_uuid[i],
            data.teams[y].teams_uuid) == 0) {
            uuid_copy(list_packet.team_uuid, data.teams[y].teams_uuid);
            strcpy(list_packet.team_name, data.teams[y].name);
            strcpy(list_packet.description, data.teams[y].description);
            send(client_fd, &list_packet, sizeof(list_packet), 0);
        }
    }
}

void list_subscribed_team(data_t data, user_t user, int client_fd)
{
    server_packet packet;

    packet.type = TYPE_SUBSCRIBED;
    packet.context = DEFAULT_CONTEXT;
    packet.nbr = user.nbr_teams;
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < user.nbr_teams; i++) {
        send_responses(data, user, i, client_fd);
    }
}
