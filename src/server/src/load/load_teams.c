/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** load_teams
*/

#include "server.h"

static void load_replies(thread_t *thread, int fd)
{
    thread->replies = malloc(sizeof(reply_t) * thread->nbr_replies);
    for (int i = 0; i < thread->nbr_replies; i++) {
        read(fd, &thread->replies[i], sizeof(thread->replies[i]));
    }
}

static void load_threads(channel_t *channel, int fd)
{
    channel->threads = malloc(sizeof(thread_t) * channel->nbr_thread);
    for (int i = 0; i < channel->nbr_thread; i++) {
        read(fd, &channel->threads[i], sizeof(channel->threads[i]));
        load_replies(&channel->threads[i], fd);
    }
}

static void load_channels(teams_t *team, int fd)
{
    team->channel = malloc(sizeof(channel_t) * team->nbr_channel);
    for (int i = 0; i < team->nbr_channel; i++) {
        read(fd, &team->channel[i], sizeof(team->channel[i]));
        load_threads(&team->channel[i], fd);
    }
}

static void load_mbr_uuids(teams_t *team, int fd)
{
    team->members_uuid = malloc(sizeof(uuid_t) * team->subs_nbr);
    for (int i = 0; i < team->subs_nbr; i++) {
        read(fd, &team->members_uuid[i], sizeof(team->members_uuid[i]));
    }
}

void load_teams(data_t *data, int fd)
{
    read(fd, &data->nbr_teams, sizeof(data->nbr_teams));
    data->teams = malloc(sizeof(teams_t) * data->nbr_teams);
    for (int i = 0; i < data->nbr_teams; i++) {
        read(fd, &data->teams[i], sizeof(data->teams[i]));
        load_mbr_uuids(&data->teams[i], fd);
        load_channels(&data->teams[i], fd);
    }
}
