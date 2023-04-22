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
    uuid_unparse(recv_data.user_uuid, user_uuid_str);
    client_event_thread_created(thread_uuid_str, user_uuid_str,
    recv_data.timestamp, recv_data.thread_title, recv_data.thread_message);
    client_print_thread_created(thread_uuid_str, user_uuid_str,
    recv_data.timestamp, recv_data.thread_title, recv_data.thread_message);
}

static void recv_create_channel(data_t *data, server_packet recv_data)
{
    char channel_uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(recv_data.channel_uuid, channel_uuid_str);
    client_event_channel_created(channel_uuid_str, recv_data.channel_name,
    recv_data.channel_desc);
    client_print_channel_created(channel_uuid_str, recv_data.channel_name,
    recv_data.channel_desc);
}

static void recv_create_reply(data_t *data, server_packet recv_data)
{
    char thread_uuid_str[MAX_UUID_LENGTH];
    char user_uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(recv_data.thread_uuid, thread_uuid_str);
    uuid_unparse(recv_data.user_uuid, user_uuid_str);
    client_print_reply_created(thread_uuid_str, user_uuid_str,
    recv_data.timestamp, recv_data.body);
}

int recv_create(client_t *client, server_packet recv_data)
{
    switch (client->data.context) {
        case DEFAULT_CONTEXT:
            recv_create_team(&client->data, recv_data);
            break;
        case REPLY_CONTEXT:
            recv_create_reply(&client->data, recv_data);
            break;
        case CHANNEL_CONTEXT:
            recv_create_channel(&client->data, recv_data);
            break;
        case THREAD_CONTEXT:
            recv_create_thread(&client->data, recv_data);
            break;
    }
    return 0;
}
