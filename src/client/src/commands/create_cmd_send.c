/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_cmd_send
*/

#include "client.h"

void send_thread_packet(client_packet *packet, data_t data, char **param)
{
    uuid_copy(packet->channel_uuid, data.context_type.channel_uuid);
    strcpy(packet->thread_title, param[0]);
    strcpy(packet->thread_message, param[1]);
}

void send_team_packet(client_packet *packet, data_t data, char **param)
{
    strcpy(packet->name, param[0]);
    packet->name_len = strlen(param[0]) + 1;
    strcpy(packet->description, param[1]);
}

void send_reply_packet(client_packet *packet, data_t data, char **param)
{
    
}
