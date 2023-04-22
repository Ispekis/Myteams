/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** communication_cmd
*/

#include "server.h"

int create_messages(user_t *users)
{
    messages_t* new_messages = realloc(users->messages,
    (users->nbr_messages + 1) * sizeof(messages_t));

    if (new_messages == NULL) {
        printf("%s\n", "malloc error");
        return 1;
    }

    users->messages = new_messages;
    users->nbr_messages++;
}

static int store_in_user(user_t *user, server_packet server_data,
uuid_t dest_uuid)
{
    uuid_copy(user->messages[user->nbr_messages - 1]
    .sender_uuid, server_data.user_uuid);
    uuid_copy(user->messages[user->nbr_messages - 1]
    .dest_uuid, dest_uuid);
    strcpy(user->messages[user->nbr_messages - 1]
    .message, server_data.message);
    user->messages[user->nbr_messages - 1]
    .message[server_data.message_len] = '\0';
    user->messages[user->nbr_messages - 1]
    .timestamp = time(NULL);
    return 0;
}

int store_message(data_t *data, server_packet server_data, uuid_t dest_uuid)
{
    for (int i = 0; i < data->nbr_users; i++) {
        if (uuid_compare(dest_uuid, data->users[i].uuid) == 0
        || uuid_compare(server_data.user_uuid, data->users[i].uuid) == 0) {
            create_messages(&data->users[i]);
            store_in_user(&data->users[i], server_data, dest_uuid);
        }
    }
    return 0;
}

void set_data(server_packet *data, client_packet recv_data)
{
    char uuid_str[37];
    char uuid_str2[37];

    uuid_unparse(recv_data.user_uuid, uuid_str);
    uuid_unparse(recv_data.dest_uuid, uuid_str2);
    server_event_private_message_sended(uuid_str, uuid_str2,
    recv_data.message);
    data->type = TYPE_SEND;
    uuid_copy(data->user_uuid, recv_data.user_uuid);
    strcpy(data->name, recv_data.name);
    strcpy(data->message, recv_data.message);
    data->message_len = recv_data.message_len;
    uuid_copy(data->dest_uuid, recv_data.dest_uuid);
}

int receive_send(server_t *server, int index, client_packet recv_data)
{
    server_packet data;

    set_data(&data, recv_data);
    for (int i = 0; i < server->data.nbr_users; i++)
        if (uuid_compare(server->data.users[i].uuid,
            recv_data.dest_uuid) == 0) {
            store_message(&server->data, data, server->data.users[i].uuid);
            send(server->data.users[i].current_fd, &data, sizeof(data), 0);
        }
    return 0;
}
