/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** save_users
*/

#include "server.h"

static void save_messages(user_t user, int fd)
{
    /*uint32_t timestamp;
    char uuid_str[MAX_UUID_LENGTH];

    write(fd, &user.nbr_messages, sizeof(user.nbr_messages));
    for (int i = 0; i < user.nbr_messages; i++) {
        write(fd, &user.messages[i].message_len,
        sizeof(user.messages[i].message_len));
        write(fd, user.messages[i].message, user.messages[i].message_len);
        timestamp = htonl(user.messages[i].timestamp);
        write(fd, &timestamp, sizeof(timestamp));
        uuid_unparse(user.messages[i].sender_uuid, uuid_str);
        write(fd, uuid_str, MAX_UUID_LENGTH);
        uuid_unparse(user.messages[i].dest_uuid, uuid_str);
        write(fd, uuid_str, MAX_UUID_LENGTH);
    }*/
}

void save_users(data_t data, int fd)
{
    char uuid_str[MAX_UUID_LENGTH];

    write(fd, &data.nbr_users, sizeof(data.nbr_users));
    for (int i = 0; i < data.nbr_users; i++) {
        write(fd, data.users[i].name, MAX_NAME_LENGTH);
        uuid_unparse(data.users[i].uuid, uuid_str);
        write(fd, uuid_str, MAX_UUID_LENGTH);
        save_messages(data.users[i], fd);
    }
}
