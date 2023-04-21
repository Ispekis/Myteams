/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create
*/

#include "client.h"

static void recv_create_thread(data_t *data, server_packet recv_data)
{
    char thread_uuid_str[MAX_UUID_LENGTH];
    char user_uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(recv_data.thread_uuid, thread_uuid_str);
    uuid_unparse(recv_data.user_uuid, recv_data.user_uuid);
    client_print_thread_created(thread_uuid_str, user_uuid_str,
    recv_data.timestamp, recv_data.thread_title, recv_data.thread_message);
    client_event_thread_created(thread_uuid_str, user_uuid_str,
    recv_data.timestamp, recv_data.thread_title, recv_data.thread_message);
}

int recv_create(client_t *client, server_packet recv_data)
{
    switch (client->data.context) {
        case DEFAULT_CONTEXT:
            recv_create_team(&client->data, recv_data);
            break;
        case REPLY_CONTEXT:
            break;
        case CHANNEL_CONTEXT:
            break;
        case THREAD_CONTEXT:
            recv_create_thread(&client->data, recv_data);
            break;
    }
    return 0;
}
