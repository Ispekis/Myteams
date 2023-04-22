/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_cmd_send
*/

#include "client.h"

int send_thread_packet(client_packet *packet, data_t data, char **param)
{
    if (param[0] == NULL || param[1] == NULL)
        return 1;
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
    uuid_copy(packet->channel_uuid, data.context_type.channel_uuid);
    strcpy(packet->thread_title, param[0]);
    strcpy(packet->thread_message, param[1]);
    return 0;
}

int send_team_packet(client_packet *packet, data_t data, char **param)
{
    if (param[0] == NULL || param[1] == NULL)
        return 1;
    strcpy(packet->name, param[0]);
    packet->name_len = strlen(param[0]) + 1;
    strcpy(packet->description, param[1]);
    return 0;
}

int send_reply_packet(client_packet *packet, data_t data, char **param)
{
    if (param[0] == NULL)
        return 1;
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
    uuid_copy(packet->channel_uuid, data.context_type.channel_uuid);
    uuid_copy(packet->thread_uuid, data.context_type.thread_uuid);
    strcpy(packet->body, param[0]);
    return 0;
}

int send_channel_packet(client_packet *packet, data_t data, char **param)
{
    if (param[0] == NULL || param[1] == NULL)
        return 1;
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
    strcpy(packet->channel_name, param[0]);
    strcpy(packet->channel_desc, param[1]);
    return 0;
}
