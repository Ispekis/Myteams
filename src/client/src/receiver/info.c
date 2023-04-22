/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** info
*/

#include "client.h"

static void recv_info_team(server_packet recv_data)
{
    char team_uuid[MAX_UUID_LENGTH];

    uuid_unparse(recv_data.team_uuid, team_uuid);
    client_print_team(team_uuid, recv_data.team_name, recv_data.description);
}

static void recv_info_channel(server_packet recv_data)
{
    char channel_uuid[MAX_UUID_LENGTH];

    uuid_unparse(recv_data.channel_uuid, channel_uuid);
    client_print_channel(channel_uuid, recv_data.channel_name,
    recv_data.channel_desc);
}

static void recv_info_thread(server_packet recv_data)
{
    char thread_uuid[MAX_UUID_LENGTH];
    char user_uuid[MAX_UUID_LENGTH];

    uuid_unparse(recv_data.thread_uuid, thread_uuid);
    uuid_unparse(recv_data.user_uuid, user_uuid);
    client_print_thread(thread_uuid, user_uuid, recv_data.timestamp,
    recv_data.thread_title, recv_data.thread_message);
}

int recv_info(client_t *client, server_packet recv_data)
{
    print_code_res(recv_data.code);
    if (recv_data.code.code == CODE_200.code) {
        switch (client->data.context) {
            case REPLY_CONTEXT:
                recv_info_thread(recv_data);
                break;
            case CHANNEL_CONTEXT:
                recv_info_team(recv_data);
                break;
            case THREAD_CONTEXT:
                recv_info_channel(recv_data);
                break;
        }
    }
    return 0;
}
