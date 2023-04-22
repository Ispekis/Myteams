/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_thread
*/

#include "server.h"

static void send_response(channel_t ch, int client_fd, int nbr_threads)
{
    server_packet packet;

    packet.type = TYPE_CREATE;
    uuid_copy(packet.thread_uuid, ch.threads[nbr_threads].thread_uuid);
    uuid_copy(packet.user_uuid, ch.threads[nbr_threads].user_uuid);
    strcpy(packet.thread_title, ch.threads[nbr_threads].thread_title);
    strcpy(packet.thread_message, ch.threads[nbr_threads].thread_body);
    packet.timestamp = ch.threads[nbr_threads].timestamp;
    send(client_fd, &packet, sizeof(packet), 0);
}

static void display_log(channel_t ch, int nbr_threads)
{
    char channel_uuid_str[MAX_UUID_LENGTH];
    char thread_uuid_str[MAX_UUID_LENGTH];
    char user_uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(ch.threads[nbr_threads].channel_uuid, channel_uuid_str);
    uuid_unparse(ch.threads[nbr_threads].thread_uuid, thread_uuid_str);
    uuid_unparse(ch.threads[nbr_threads].user_uuid, user_uuid_str);
    server_event_thread_created(channel_uuid_str, thread_uuid_str,
    user_uuid_str, ch.threads[nbr_threads].thread_title,
    ch.threads[nbr_threads].thread_body);
}

static void set_data(channel_t *ch, client_packet recv_data, int nbr_threads)
{
    uuid_generate(ch->threads[nbr_threads].thread_uuid);
    uuid_copy(ch->threads[nbr_threads].user_uuid, recv_data.user_uuid);
    uuid_copy(ch->threads[nbr_threads].channel_uuid,
    recv_data.channel_uuid);
    strcpy(ch->threads[nbr_threads].thread_title, recv_data.thread_title);
    strcpy(ch->threads[nbr_threads].thread_body,
    recv_data.thread_message);
    ch->threads[nbr_threads].timestamp = time(NULL);
    ch->threads[nbr_threads].nbr_replies = 0;
    ch->threads[nbr_threads].replies = malloc(sizeof(reply_t));
}

int create_thread(data_t *data, int client_fd, client_packet recv_data)
{
    channel_t *channel = index_of_channel(data, recv_data);
    thread_t *new_thread;

    if (channel == NULL) {
        printf("Not found\n");
        return 0;
    }
    new_thread = realloc(channel->threads,
    sizeof(thread_t) * (channel->nbr_thread + 1));
    if (new_thread == NULL)
        return 1;
    channel->threads = new_thread;
    set_data(channel, recv_data,
    channel->nbr_thread);
    display_log(*channel, channel->nbr_thread);
    send_response(*channel, client_fd,
    channel->nbr_thread);
    channel->nbr_thread++;
    return 0;
}
