/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** list_context
*/

#include "server.h"

void list_team(data_t data, int client_fd, client_packet recv_data)
{
    server_packet packet;
    server_packet list_packet;

    packet.type = TYPE_LIST;
    packet.nbr = data.nbr_teams;
    packet.code = CODE_200;
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < data.nbr_teams; i++) {
        uuid_copy(list_packet.team_uuid, data.teams[i].teams_uuid);
        strcpy(list_packet.team_name, data.teams[i].name);
        strcpy(list_packet.description, data.teams[i].description);
        send(client_fd, &list_packet, sizeof(list_packet), 0);
    }
}

void list_channel(data_t data, int client_fd, client_packet recv_data)
{
    teams_t *team = index_of_team(&data, recv_data);
    server_packet packet;
    server_packet list_packet;

    if (team == NULL)
        return;
    packet.type = TYPE_LIST;
    packet.code = CODE_200;
    packet.nbr = data.nbr_teams;
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < team->nbr_channel; i++) {
        uuid_copy(list_packet.channel_uuid, team->channel[i].uuid);
        strcpy(list_packet.channel_name, team->channel[i].name);
        strcpy(list_packet.channel_desc, team->channel[i].description);
        send(client_fd, &list_packet, sizeof(list_packet), 0);
    }
}

void list_thread(data_t data, int client_fd, client_packet recv_data)
{
    channel_t *channel = index_of_channel(&data, recv_data);
    server_packet packet;
    server_packet list_packet;

    if (channel == NULL)
        return;
    packet.type = TYPE_LIST;
    packet.code = CODE_200;
    packet.nbr = channel->nbr_thread;
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < channel->nbr_thread; i++) {
        uuid_copy(list_packet.thread_uuid, channel->threads[i].thread_uuid);
        uuid_copy(list_packet.user_uuid, channel->threads[i].user_uuid);
        list_packet.timestamp = channel->threads[i].timestamp;
        strcpy(list_packet.thread_title, channel->threads[i].thread_title);
        strcpy(list_packet.thread_message, channel->threads[i].thread_body);
        send(client_fd, &list_packet, sizeof(list_packet), 0);
    }
}

void list_reply(data_t data, int client_fd, client_packet recv_data)
{
    thread_t *thread = index_of_thread(&data, recv_data);
    server_packet packet;
    server_packet list_packet;

    if (thread == NULL)
        return;
    packet.type = TYPE_LIST;
    packet.code = CODE_200;
    packet.nbr = thread->nbr_replies;
    send(client_fd, &packet, sizeof(packet), 0);
    for (int i = 0; i < thread->nbr_replies; i++) {
        uuid_copy(list_packet.thread_uuid, thread->thread_uuid);
        uuid_copy(list_packet.user_uuid, thread->replies[i].user_uuid);
        list_packet.timestamp = thread->replies[i].timestamp;
        strcpy(list_packet.body, thread->replies[i].body);
        send(client_fd, &list_packet, sizeof(list_packet), 0);
    }
}
