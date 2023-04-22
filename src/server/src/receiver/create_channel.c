/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** manage_channel
*/

#include "server.h"

static int create_channel(teams_t *team, int nbr_channel,
client_packet recv_data)
{
    channel_t* new_channel = realloc(team->channel,
    (nbr_channel + 1) * sizeof(channel_t));
    if (new_channel == NULL)
        return 1;

    team->channel = new_channel;
    strcpy(team->channel[nbr_channel].name, recv_data.channel_name);
    strcpy(team->channel[nbr_channel].description, recv_data.channel_desc);
    uuid_generate(team->channel[nbr_channel].uuid);
    team->channel[nbr_channel].nbr_thread = 0;
    team->channel[nbr_channel].threads = malloc(sizeof(thread_t));
    return 0;
}

static void display_log(teams_t team, int index)
{
    char team_uuid_str[MAX_UUID_LENGTH];
    char channel_uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(team.teams_uuid, team_uuid_str);
    uuid_unparse(team.channel[index].uuid, channel_uuid_str);
    server_event_channel_created(team_uuid_str, channel_uuid_str,
    team.channel[index].name);
}

static void send_response(teams_t team, int client_fd, int index)
{
    server_packet packet;

    packet.type = TYPE_CREATE;
    uuid_copy(packet.channel_uuid, team.channel[index].uuid);
    strcpy(packet.channel_name, team.channel[index].name);
    strcpy(packet.channel_desc, team.channel[index].description);
    send(client_fd, &packet, sizeof(packet), 0);
}

int receive_channel(data_t *data, int client_fd, client_packet recv_data)
{
    char uuid_str[MAX_UUID_LENGTH];
    char team_uuid[MAX_UUID_LENGTH];
    teams_t *team = index_of_team(data, recv_data);

    if (team == NULL) {
        printf("Not found\n");
        return 0;
    }
    create_channel(team, team->nbr_channel, recv_data);
    display_log(*team, team->nbr_channel);
    uuid_unparse(recv_data.user_uuid, uuid_str);
    uuid_unparse(team->teams_uuid, team_uuid);
    join_teams(data, uuid_str, team_uuid);
    member_add_team(data, uuid_str, team_uuid);
    send_response(*team, client_fd, team->nbr_channel);
    team->nbr_channel++;
    return 0;
}
