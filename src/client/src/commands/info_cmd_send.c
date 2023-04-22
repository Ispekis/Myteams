/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** info_cmd_send
*/

#include "client.h"

void do_default_info(data_t data)
{
    char uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(data.user_uuid, uuid_str);
    client_print_user(uuid_str, data.user_name, data.is_logged);
}

void send_info_team(client_packet *packet, data_t data)
{
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
}

void send_info_channel(client_packet *packet, data_t data)
{
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
    uuid_copy(packet->channel_uuid, data.context_type.channel_uuid);
}

void send_info_thread(client_packet *packet, data_t data)
{
    uuid_copy(packet->team_uuid, data.context_type.team_uuid);
    uuid_copy(packet->channel_uuid, data.context_type.channel_uuid);
    uuid_copy(packet->thread_uuid, data.context_type.thread_uuid);
}
