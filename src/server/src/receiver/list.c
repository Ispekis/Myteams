/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** list
*/

#include "server.h"

int receive_list_teams(server_t *server, int index, client_packet recv_data)
{
    server_packet data;
    data.type = TYPE_LIST;

    for (int i = 0; i < server->data.nbr_teams; i++) {
        uuid_copy(data.team_uuid, server->data.teams[i].teams_uuid);
        strcpy(data.team_name, server->data.teams[i].name);
        strcpy(data.description, server->data.teams[i].description);
        send(server->addrs.clients[index].fd, &data, sizeof(data), 0);
    }
    return 0;
}
