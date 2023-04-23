/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** save_teams
*/

#include "server.h"

void save_replies(thread_t thread, int fd)
{
    for (int i = 0; i < thread.nbr_replies; i++) {
        write(fd, &thread.replies[i], sizeof(thread.replies[i]));
    }
}

void save_threads(channel_t channel, int fd)
{
    for (int i = 0; i < channel.nbr_thread; i++) {
        write(fd, &channel.threads[i], sizeof(channel.threads[i]));
        save_replies(channel.threads[i], fd);
    }
}

void save_channels(teams_t team, int fd)
{
    for (int i = 0; i < team.nbr_channel; i++) {
        write(fd, &team.channel[i], sizeof(team.channel[i]));
        save_threads(team.channel[i], fd);
    }
}

void save_teams_mbr_uuids(teams_t team, int fd)
{
    for (int i = 0; i < team.subs_nbr; i++) {
        write(fd, &team.members_uuid[i], sizeof(team.members_uuid[i]));
    }
}

void save_teams(data_t data, int fd)
{
    write(fd, &data.nbr_teams, sizeof(data.nbr_teams));
    for (int i = 0; i < data.nbr_teams; i++) {
        write(fd, &data.teams[i], sizeof(data.teams[i]));
        save_teams_mbr_uuids(data.teams[i], fd);
        save_channels(data.teams[i], fd);
    }
}
