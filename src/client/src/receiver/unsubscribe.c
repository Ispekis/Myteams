/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** unsubscribe
*/

#include "client.h"

int recv_unsubscribe(client_t *client, server_packet recv_data)
{
    char team_uuid[37];
    char user_uuid[37];

    uuid_unparse(recv_data.team_uuid, team_uuid);
    if (recv_data.code.code == CODE_200.code) {
        uuid_unparse(recv_data.user_uuid, user_uuid);
        client_print_unsubscribed(user_uuid, team_uuid);
    } else
        client_error_unknown_team(team_uuid);
    return 0;
}
