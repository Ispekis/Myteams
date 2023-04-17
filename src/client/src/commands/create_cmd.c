/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** create_cmd
*/

#include "client.h"

int create_sub_res(client_t *client, char **param)
{
    client_packet packet;

    if (!client->data.is_logged) {
        printf("Not logged\n");
        return 0;
    }

    if (param[0] == NULL || param[1] == NULL) {
        printf("Invalid arguments\n");
        return 0;
    }
    return 0;
}
