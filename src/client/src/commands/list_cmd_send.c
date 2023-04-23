/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** list_cmd_send
*/

#include "client.h"

void send_list_team(client_packet *packet, data_t data)
{

}

void send_list_channel(client_packet *packet, data_t data)
{
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
}

void send_list_thread(client_packet *packet, data_t data)
{
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
    uuid_copy(packet->channel_uuid, data.context_type.channel_uuid);
}

void send_list_reply(client_packet *packet, data_t data)
{
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
    uuid_copy(packet->channel_uuid, data.context_type.channel_uuid);
    uuid_copy(packet->thread_uuid, data.context_type.thread_uuid);
}