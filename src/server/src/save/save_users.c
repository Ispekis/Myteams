/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** save_users
*/

#include "server.h"

void save_users(data_t data, int fd)
{
    write(fd, &data.nbr_users, sizeof(data.nbr_users));
    for (int i = 0; i < data.nbr_users; i++) {
        write(fd, &data.users[i], sizeof(data.users[i]));
        for (int y = 0; y < data.users[i].nbr_messages; y++)
            write(fd, &data.users[i].messages[y],
            sizeof(data.users[i].messages[y]));
    }
}
