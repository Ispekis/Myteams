/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribe
*/

#include "client.h"

int recv_subscribe(client_t *client, server_packet recv_data)
{
    char team_uuid[37];
    char user_uuid[37];

    uuid_unparse(recv_data.team_uuid, team_uuid);
    uuid_unparse(recv_data.user_uuid, user_uuid);
    client_print_subscribed(team_uuid, user_uuid);
    return 0;
}
