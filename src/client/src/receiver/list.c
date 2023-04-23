/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** list
*/

#include "client.h"

static void recv_list_team(int server_fd, server_packet recv_data)
{
    char team_uuid[MAX_UUID_LENGTH];
    server_packet list_packet;

    for (int i = 0; i < recv_data.nbr; i++) {
        recv(server_fd, &list_packet, sizeof(list_packet), 0);
        uuid_unparse(list_packet.team_uuid, team_uuid);
        client_print_team(team_uuid, list_packet.team_name, list_packet.description);
    }
}

static void recv_list_channel(int server_fd, server_packet recv_data)
{
    char channel_uuid[MAX_UUID_LENGTH];
    server_packet list_packet;

    for (int i = 0; i < recv_data.nbr; i++) {
        recv(server_fd, &list_packet, sizeof(list_packet), 0);
        uuid_unparse(list_packet.channel_uuid, channel_uuid);
        client_team_print_channels(channel_uuid, list_packet.channel_name, list_packet.channel_desc);
    }
}

static void recv_list_thread(int server_fd, server_packet recv_data)
{
    char thread_uuid[MAX_UUID_LENGTH];
    char user_uuid[MAX_UUID_LENGTH];
    server_packet list_packet;

    for (int i = 0; i < recv_data.nbr; i++) {
        recv(server_fd, &list_packet, sizeof(list_packet), 0);
        uuid_unparse(list_packet.thread_uuid, thread_uuid);
        uuid_unparse(list_packet.user_uuid, user_uuid);
        client_channel_print_threads(thread_uuid, user_uuid,
        list_packet.timestamp, list_packet.thread_title,
        list_packet.thread_message);
    }
}

static void recv_list_reply(int server_fd, server_packet recv_data)
{
    char thread_uuid[MAX_UUID_LENGTH];
    char user_uuid[MAX_UUID_LENGTH];
    server_packet list_packet;

    for (int i = 0; i < recv_data.nbr; i++) {
        recv(server_fd, &list_packet, sizeof(list_packet), 0);
        uuid_unparse(list_packet.thread_uuid, thread_uuid);
        uuid_unparse(list_packet.user_uuid, user_uuid);
        client_thread_print_replies(thread_uuid, user_uuid,
        list_packet.timestamp, list_packet.body);
    }
}

int recv_list(client_t *client, server_packet recv_data)
{
    print_code_res(recv_data.code);
    if (recv_data.code.code == CODE_200.code) {
        switch (client->data.context) {
            case DEFAULT_CONTEXT:
                recv_list_team(client->addrs.server_fd, recv_data);
                break;
            case REPLY_CONTEXT:
                recv_list_reply(client->addrs.server_fd, recv_data);
                break;
            case CHANNEL_CONTEXT:
                recv_list_channel(client->addrs.server_fd, recv_data);
                break;
            case THREAD_CONTEXT:
                recv_list_thread(client->addrs.server_fd, recv_data);
                break;
        }
    }
    return 0;
}
