/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_reply
*/

#include "server.h"

static int create_new_reply(thread_t *thread, client_packet recv_data)
{
    reply_t *new_reply = realloc(thread->replies,
    sizeof(reply_t) * (thread->nbr_replies + 1));

    if (new_reply == NULL)
        return 1;
    thread->replies = new_reply;
    uuid_copy(thread->replies[thread->nbr_replies].user_uuid,
    recv_data.user_uuid);
    thread->replies[thread->nbr_replies].timestamp = time(NULL);
    strcpy(thread->replies[thread->nbr_replies].body, recv_data.body);
    return 0;
}

static void display_log(thread_t *thread, client_packet recv_data)
{
    char thread_uuid_str[MAX_UUID_LENGTH];
    char user_uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(thread->thread_uuid, thread_uuid_str);
    uuid_unparse(thread->replies[thread->nbr_replies].user_uuid,
    user_uuid_str);
    server_event_reply_created(thread_uuid_str, user_uuid_str,
    thread->replies[thread->nbr_replies].body);
}

static void send_response(thread_t *thread, int client_fd)
{
    server_packet packet;

    packet.type = TYPE_CREATE;
    uuid_copy(packet.thread_uuid, thread->thread_uuid);
    uuid_copy(packet.user_uuid,
    thread->replies[thread->nbr_replies].user_uuid);
    strcpy(packet.body, thread->replies[thread->nbr_replies].body);
    packet.timestamp = thread->replies[thread->nbr_replies].timestamp;
    send(client_fd, &packet, sizeof(packet), 0);
}

int create_reply(data_t *data, int client_fd, client_packet recv_data)
{
    thread_t *thread = index_of_thread(data, recv_data);

    if (thread == NULL) {
        printf("NotFound\n");
        return 0;
    }
    if (create_new_reply(thread, recv_data) == 1)
        return 0;
    display_log(thread, recv_data);
    send_response(thread, client_fd);
    thread->nbr_replies++;
    return 0;
}
