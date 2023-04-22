/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** subscribed
*/

#include "client.h"

int recv_subscribed(client_t *client, server_packet recv_data)
{
    char tmp_uuid[37];

    if (recv_data.context == 0) {
        uuid_unparse(recv_data.team_uuid, tmp_uuid);
        client_print_team(tmp_uuid, recv_data.team_name, recv_data.description);
    } else {
        if (recv_data.code.code == 200) {
            uuid_unparse(recv_data.user_uuid, tmp_uuid);
            client_print_user(tmp_uuid, recv_data.name, recv_data.status);
        } else {
            uuid_unparse(recv_data.team_uuid, tmp_uuid);
            client_error_unknown_team(tmp_uuid);
        }
    }
    return 0;
}
