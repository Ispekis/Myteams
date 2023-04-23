/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** load_users
*/

#include "server.h"

static void load_messages(user_t *user, int fd)
{
    user->messages = malloc(sizeof(messages_t) * user->nbr_messages);
    for (int i = 0; i < user->nbr_messages; i++) {
        read(fd, &user->messages[i], sizeof(user->messages[i]));
    }
}

static void load_teams_uuids(user_t *user, int fd)
{
    user->teams_uuid = malloc(sizeof(uuid_t) * user->nbr_teams);
    for (int i = 0; i < user->nbr_teams; i++) {
        read(fd, &user->teams_uuid[i], sizeof(user->teams_uuid[i]));
    }
}

void load_users(data_t *data, int fd)
{
    char uuid_str[MAX_UUID_LENGTH];

    read(fd, &data->nbr_users, sizeof(data->nbr_users));
    data->users = malloc(sizeof(user_t) * data->nbr_users);
    for (int i = 0; i < data->nbr_users; i++) {
        read(fd, &data->users[i], sizeof(data->users[i]));
        load_teams_uuids(&data->users[i], fd);
        load_messages(&data->users[i], fd);

        uuid_unparse(data->users[i].uuid, uuid_str);
        server_event_user_loaded(uuid_str, data->users[i].name);
    }
}
