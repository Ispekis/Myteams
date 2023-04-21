/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_thread
*/

#include "server.h"

static void send_response(data_t data, int client_fd)
{
    server_packet packet;

    packet.type = TYPE_CREATE;
    uuid_copy(packet.thread_uuid, data.threads[data.nbr_thread].thread_uuid);
    uuid_copy(packet.user_uuid, data.threads[data.nbr_thread].user_uuid);
    strcpy(packet.thread_title, data.threads[data.nbr_thread].thread_title);
    strcpy(packet.thread_message, data.threads[data.nbr_thread].thread_body);
    packet.timestamp = data.threads[data.nbr_thread].timestamp;
    send(client_fd, &packet, sizeof(packet), 0);
}

static void display_log(data_t data)
{
    char channel_uuid_str[MAX_UUID_LENGTH];
    char thread_uuid_str[MAX_UUID_LENGTH];
    char user_uuid_str[MAX_UUID_LENGTH];

    uuid_unparse(data.threads[data.nbr_thread].channel_uuid, channel_uuid_str);
    uuid_unparse(data.threads[data.nbr_thread].thread_uuid, thread_uuid_str);
    uuid_unparse(data.threads[data.nbr_thread].user_uuid, user_uuid_str);
    server_event_thread_created(channel_uuid_str, thread_uuid_str,
    user_uuid_str, data.threads[data.nbr_thread].thread_title,
    data.threads[data.nbr_thread].thread_body);
}

int create_thread(data_t *data, int client_fd, client_packet recv_data)
{
    char uuid_str[MAX_UUID_LENGTH];
    thread_t *new_thread = realloc(data->threads,
    sizeof(thread_t) * (data->nbr_thread + 1));

    if (new_thread == NULL)
        return 1;
    data->threads = new_thread;
    uuid_generate(data->threads[data->nbr_teams].thread_uuid);
    uuid_copy(data->threads->user_uuid, recv_data.user_uuid);
    uuid_copy(data->threads[data->nbr_thread].channel_uuid,
    recv_data.channel_uuid);
    strcpy(data->threads[data->nbr_teams].thread_title, recv_data.thread_title);
    strcpy(data->threads[data->nbr_teams].thread_body,
    recv_data.thread_message);
    data->threads[data->nbr_thread].timestamp = time(NULL);
    display_log(*data);
    send_response(*data, client_fd);
    data->nbr_teams++;
    return 0;
}
