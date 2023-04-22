/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** save_backup
*/

#include "server.h"

void load_save(server_t *server)
{
    int fd = open(save_file_name, O_RDONLY);
    int bytes;

    if (fd != -1) {
        load_users(&server->data, fd);
    }
    close(fd);
}

static void save_data(server_t server)
{
    int fd = open(save_file_name, O_CREAT | O_WRONLY, 0644);

    for (int i = 0; i < server.data.nbr_users; i++) {
        server.data.users[i].is_logged = false;
    }
    save_users(server.data, fd);
    close(fd);
}

int catch_shutdown(server_t server)
{
    if (FD_ISSET(server.sfd, &server.addrs.rfds)) {
        read(server.sfd, &server.fdsi, sizeof(struct signalfd_siginfo));
        if (server.fdsi.ssi_signo == SIGINT) {
            save_data(server);
            return 1;
        }
    }
    return 0;
}
