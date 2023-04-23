/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** info_context
*/

#include "server.h"

void info_team(data_t data, int client_fd, client_packet recv_data)
{
    teams_t *team = index_of_team(&data, recv_data);
    server_packet packet;

    if (team == NULL)
        return;
    packet.type = TYPE_INFO;
    packet.code = CODE_200;
    uuid_copy(packet.team_uuid, team->teams_uuid);
    strcpy(packet.team_name, team->name);
    strcpy(packet.description, team->description);
    send(client_fd, &packet, sizeof(packet), 0);
}

void info_channel(data_t data, int client_fd, client_packet recv_data)
{
    channel_t *channel = index_of_channel(&data, recv_data);
    server_packet packet;

    if (channel == NULL)
        return;
    packet.type = TYPE_INFO;
    packet.code = CODE_200;
    uuid_copy(packet.channel_uuid, channel->uuid);
    strcpy(packet.channel_name, channel->name);
    strcpy(packet.channel_desc, channel->description);
    send(client_fd, &packet, sizeof(packet), 0);
}

void info_thread(data_t data, int client_fd, client_packet recv_data)
{
    thread_t *thread = index_of_thread(&data, recv_data);
    server_packet packet;

    if (thread == NULL)
        return;
    packet.type = TYPE_INFO;
    packet.code = CODE_200;
    uuid_copy(packet.thread_uuid, thread->thread_uuid);
    uuid_copy(packet.user_uuid, thread->user_uuid);
    packet.timestamp = thread->timestamp;
    strcpy(packet.thread_title, thread->thread_title);
    strcpy(packet.thread_message, thread->thread_body);
    send(client_fd, &packet, sizeof(packet), 0);
}
