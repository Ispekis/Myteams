/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** save_backup
*/

#include "server.h"

static server_t *sig_server = NULL;

void load_save(server_t *server)
{
    int fd = open(save_file_name, O_RDONLY);
    int bytes;

    if (fd != -1) {
        bytes = read(fd, &server->data, sizeof(server->data));
        close(fd);
    }
}

static void signal_handler(int sig)
{
    int fd = open(save_file_name, O_CREAT | O_WRONLY, 0644);

    for (int i = 0; i < sig_server->data.nbr_users; i++) {
        sig_server->data.users[i].is_logged = false;
    }
    write(fd, &sig_server->data, sizeof(sig_server->data));
    close(fd);
}

void catch_shutdown(server_t *server)
{
    sig_server = server;
    signal(SIGINT, signal_handler);
}
