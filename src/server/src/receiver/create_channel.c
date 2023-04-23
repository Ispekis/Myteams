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
    packet.code = CODE_200;
    uuid_copy(packet.channel_uuid, team.channel[index].uuid);
    strcpy(packet.channel_name, team.channel[index].name);
    strcpy(packet.channel_desc, team.channel[index].description);
    send(client_fd, &packet, sizeof(packet), 0);
}

static int check_known_channel(teams_t *team, int client_fd, client_packet
recv_data)
{
    server_packet packet;

    for (int i = 0; i < team->nbr_channel; ++i) {
        if (strcmp(recv_data.channel_name, team->channel[i].name) == 0) {
            packet.code = CODE_400;
            packet.type = TYPE_CREATE;
            packet.context = CHANNEL_CONTEXT;
            send(client_fd, &packet, sizeof(packet), 0);
            return -1;
        }
    }
    return 0;
}

int receive_channel(data_t *data, int client_fd, client_packet recv_data)
{
    teams_t *team = index_of_team(data, recv_data);
    user_t *user = index_of_user(data, recv_data.user_uuid);

    if (team == NULL) {
        printf("Not found\n");
        return 0;
    }
    if (check_known_channel(team, client_fd, recv_data) == -1)
        return 1;
    create_channel(team, team->nbr_channel, recv_data);
    display_log(*team, team->nbr_channel);
    send_response(*team, client_fd, team->nbr_channel);
    team->nbr_channel++;
    return 0;
}
