/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** use
*/

#include "client.h"

static void set_channel_context(data_t *data, server_packet recv_data)
{
    uuid_copy(data->context_type.team_uuid, recv_data.team_uuid);
}

static void set_thread_context(data_t *data, server_packet recv_data)
{
    set_channel_context(data, recv_data);
    uuid_copy(data->context_type.channel_uuid, recv_data.channel_uuid);
}

static void set_reply_context(data_t *data, server_packet recv_data)
{
    set_thread_context(data, recv_data);
    uuid_copy(data->context_type.thread_uuid, recv_data.thread_uuid);
}

void empty_context_uuid(context_type_t *ctxt)
{
    uuid_clear(ctxt->team_uuid);
    uuid_clear(ctxt->channel_uuid);
    uuid_clear(ctxt->thread_uuid);
}

int recv_use(client_t *client, server_packet recv_data)
{
    print_code_res(recv_data.code);
    if (recv_data.code.code == CODE_200.code) {
        empty_context_uuid(&client->data.context_type);
        client->data.context = recv_data.context;
        switch (client->data.context) {
            case DEFAULT_CONTEXT:
                break;
            case CHANNEL_CONTEXT:
                set_channel_context(&client->data, recv_data);
                break;
            case THREAD_CONTEXT:
                set_thread_context(&client->data, recv_data);
                break;
            case REPLY_CONTEXT:
                set_reply_context(&client->data, recv_data);
                break;
        }
    }
    return 0;
}
