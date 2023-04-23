/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** save_users
*/

#include "server.h"

static void save_messages(user_t user, int fd)
{
    for (int i = 0; i < user.nbr_messages; i++) {
        write(fd, &user.messages[i], sizeof(user.messages[i]));
    }
}

static void save_teams_uuids(user_t user, int fd)
{
    for (int i = 0; i < user.nbr_teams; i++) {
        write(fd, &user.teams_uuid[i], sizeof(user.teams_uuid[i]));
    }
}

void save_users(data_t data, int fd)
{
    write(fd, &data.nbr_users, sizeof(data.nbr_users));
    for (int i = 0; i < data.nbr_users; i++) {
        write(fd, &data.users[i], sizeof(data.users[i]));
        save_teams_uuids(data.users[i], fd);
        save_messages(data.users[i], fd);
    }
}
