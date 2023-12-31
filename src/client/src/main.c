/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** main
*/

#include "client.h"

void show_usage(char *binary, int fd)
{
    dprintf(fd, "USAGE:\t%s ip port\n", binary);
    dprintf(fd, "\tip\tis the server ip address on which the server");
    dprintf(fd, " socket listens\n");
    dprintf(fd, "\tport\tis the port number on which the server");
    dprintf(fd, " socket listens\n");
}

int main(int argc, char **argv)
{
    if ((argc == 2 && strcmp(argv[1], "-help") == 0)) {
        show_usage(argv[0], STDOUT_FILENO);
        return 0;
    }
    if (error_handling(argc, argv) == 1)
        return 84;
    if (run_client(argv[1], atoi(argv[2])) == 1)
        return 84;
    return 0;
}
