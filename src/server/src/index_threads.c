/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** index_threads
*/

#include "server.h"

channel_t *index_of_channel(data_t *data, client_packet recv_data)
{
    teams_t *team = index_of_team(data, recv_data);

    if (team == NULL)
        return NULL;
    for (int i = 0; i < team->nbr_channel; i++) {
        if (uuid_compare(team->channel[i].uuid, recv_data.channel_uuid) == 0) {
            return &team->channel[i];
        }
    }
    return NULL;
}

thread_t *index_of_thread(data_t *data, client_packet recv_data)
{
    channel_t *channel = index_of_channel(data, recv_data);

    if (channel == NULL)
        return NULL;
    for (int i = 0; i < channel->nbr_thread; i++) {
        if (uuid_compare(channel->threads[i].thread_uuid,
            recv_data.thread_uuid) == 0) {
            return &channel->threads[i];
        }
    }
    return NULL;
}

teams_t *index_of_team(data_t *data, client_packet recv_data)
{
    for (int i = 0; i < data->nbr_teams; i++) {
        if (uuid_compare(data->teams[i].teams_uuid, recv_data.team_uuid) == 0) {
            return &data->teams[i];
        }
    }
    return NULL;
}

user_t *index_of_user(data_t *data, uuid_t user_uuid)
{
    for (int i = 0; i < data->nbr_users; i++) {
        if (uuid_compare(data->users[i].uuid, user_uuid) == 0) {
            return &data->users[i];
        }
    }
    return NULL;
}
