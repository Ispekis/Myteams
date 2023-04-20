/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** load_users
*/

#include "server.h"

void load_messages(user_t *user, int fd)
{
    char uuid_str[MAX_UUID_LENGTH];
    uint32_t timestamp;

    read(fd, &user->nbr_messages, sizeof(user->nbr_messages));
    user->messages = malloc(sizeof(messages_t) * user->nbr_messages);
    for (int i = 0; i < user->nbr_messages; i++) {
        read(fd, &user->messages[i].message_len,
        sizeof(user->messages[i].message_len));
        user->messages[i].message = malloc(sizeof(char) *
        user->messages[i].message_len);
        read(fd, user->messages[i].message, user->messages[i].message_len);
        user->messages[i].message[user->messages[i].message_len - 1] = '\0';
        read(fd, &timestamp, sizeof(timestamp));
        user->messages[i].timestamp = ntohl(timestamp);
        read(fd, uuid_str, MAX_UUID_LENGTH);
        uuid_parse(uuid_str, user->messages[i].sender_uuid);
        read(fd, uuid_str, MAX_UUID_LENGTH);
        uuid_parse(uuid_str, user->messages[i].dest_uuid);
    }
}

void load_users(data_t *data, int fd)
{
    char uuid_str[MAX_UUID_LENGTH];

    read(fd, &data->nbr_users, sizeof(data->nbr_users));
    for (int i = 0; i < data->nbr_users; i++) {
        read(fd, data->users[i].name, MAX_NAME_LENGTH);
        read(fd, uuid_str, MAX_UUID_LENGTH);
        uuid_parse(uuid_str, data->users[i].uuid);
        load_messages(&data->users[i], fd);
    }
}
