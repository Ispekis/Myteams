/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** cli_management
*/

#include "server.h"

int get_cli_events(server_t *server, char* input, int index)
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
            server->cmd[cmd_pos](server, params, index);
    }
    return 0;
}
