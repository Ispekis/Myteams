/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** load_users
*/

#include "server.h"

void load_users(data_t *data, int fd)
{
    read(fd, &data->nbr_users, sizeof(data->nbr_users));
    data->users = malloc(sizeof(user_t) * data->nbr_users);
    for (int i = 0; i < data->nbr_users; i++) {
        read(fd, &data->users[i], sizeof(data->users[i]));
        data->users[i].messages = malloc(sizeof(messages_t) *
        data->users[i].nbr_messages);
        for (int y = 0; y < data->users[i].nbr_messages; y++) {
            read(fd, &data->users[i].messages[i],
            sizeof(data->users[i].messages[i]));
        }
    }
}
