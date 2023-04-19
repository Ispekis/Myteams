/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** login
*/

#include "client.h"

static int recv_success(client_t *client, server_packet recv_data)
{
    char uuid_str[37];

    uuid_unparse(recv_data.user_uuid, uuid_str);
    client_event_logged_in(uuid_str, recv_data.name);
    client->data.is_logged = true;
    client->data.context = recv_data.context;
    strcpy(client->data.user_name, recv_data.name);
    uuid_copy(client->data.user_uuid, recv_data.user_uuid);
    return 0;
}

static int recv_failure(void)
{
    printf("User already logged\n");
    return 0;
}

int recv_login(client_t *client, server_packet recv_data)
{

    if (recv_data.code.code == CODE_200.code) {
        recv_success(client, recv_data);
    } else {
        recv_failure();
    }
    return 0;
}
