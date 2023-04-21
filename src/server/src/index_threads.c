/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** index_threads
*/

#include "server.h"

int index_of_channel(data_t data, int max_len, uuid_t uuid)
{
    for (int i = 0; i < max_len; i++)
        if (uuid_compare(data.channel[i].uuid, uuid) == 0)
            return i;
    return -1;
}

int index_of_thread()
{

}