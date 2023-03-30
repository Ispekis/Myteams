/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <ctype.h>


// typedef struct sock_addrs {
//     struct sockaddr_in server;
//     struct timeval timeout;
//     int socket_fd;
//     int name;
//     int status;
//     char *pathname;
//     fd_set rfds;
// } sock_addrs_t;

// typedef struct client {
//     sock_addrs_t addrs;
//     int (*cmd[TOTAL_CMD])(struct client* client, char** param, int index);
// } client_t;

int error_handling(int ac, char **av);

// client.c
int run_client(char *ip, int port);

#endif /* !CLIENT_H_ */
