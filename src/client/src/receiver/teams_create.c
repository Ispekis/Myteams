/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** teams_create
*/

#include "client.h"

int recv_create_team(data_t *data, server_packet recv_data)
{
    char team_uuid[37];

    if (recv_data.code.code == 200) {
        uuid_unparse(recv_data.team_uuid, team_uuid);
        client_event_team_created(team_uuid, recv_data.name,
        recv_data.description);
    } else
        client_error_already_exist();
    return 0;
}
