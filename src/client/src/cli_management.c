/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** cli_management
*/

#include "client.h"

static int choose_cmd(client_t *client, char *cmd, char** params)
{
    int cmd_pos;

    if (cmd[0] == '/') {
        cmd++;
        cmd_pos = get_cmd_pos(cmd);
        if (cmd_pos != -1)
            client->cmd[cmd_pos](client, params);
    }
}

int get_cli_events(client_t *client, char* input)
{
    char **params = NULL;
    char *cmd;

    cmd = get_cmd(&input);
    if (cmd == NULL) {
        cmd = input;
    } else {
        if (nbr_params(input) == -1)
            return 0;
        params = get_params(input);
        if (params == NULL) {
            return 0;
        }
    }
    choose_cmd(client, cmd, params);
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
