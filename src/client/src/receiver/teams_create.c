/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** teams_create
*/

#include "client.h"

int recv_create_team(client_t *client, server_packet recv_data)
{
    char team_uuid[37];

    uuid_unparse(recv_data.team_uuid, team_uuid);
    client_event_team_created(team_uuid, recv_data.name,
    recv_data.description);
    return 0;
}
