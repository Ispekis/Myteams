/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** cli_management
*/

#include "client.h"

int get_cli_events(client_t *client, char* input)
{
    char **params;
    int nbr_params = str_to_array(&params, input, " \t");
    char *cmd;
    int cmd_pos;

    if (nbr_params == 0)
        return 0;
    cmd = strdup(params[0]);
    params++;
    if (cmd[0] == '/') {
        cmd++;
        cmd_pos = get_cmd_pos(cmd);
        if (cmd_pos != -1)
            client->cmd[cmd_pos](client, params);
    }
    return 0;
}

int read_client_cli(client_t *client)
{
    char *buffer = NULL;
    size_t len = 0;

    if (FD_ISSET(STDIN_FILENO, &client->addrs.rfds)) {
        getline(&buffer, &len, stdin);
        get_cli_events(client, removing_line_break(buffer));
        memset(buffer, '\0', sizeof(buffer));
    }
    return 0;
}