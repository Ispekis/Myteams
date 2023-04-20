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
    if (param == NULL || param[0] == NULL || param[1] == NULL) {
        printf("Invalid arguments\n");
        return 0;
    }
    packet.type = TYPE_CREATE_TEAM;
    uuid_copy(packet.user_uuid, client->data.user_uuid);
    strcpy(packet.name, param[0]);
    packet.name_len = strlen(param[0]) + 1;
    strcpy(packet.description, param[1]);
    send(client->addrs.server_fd, &packet, sizeof(packet), 0);
    return 0;
}
