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
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <stddef.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #define TOTAL_CMD 15
    #define MAX_CONNECTIONS 100

static const char *CMD_LIB[] = {"help", "login", "logout", "users", "user",
"send", "messages", "subscribe", "subscribed", "unsubscribe", "use", "create",
"list", "info", NULL};

enum cmd_e {
    HELP,
    LOGIN,
    LOGOUT,
    USERS,
    USER,
    SEND,
    MESSAGES,
    SUBSCRIBE,
    SUBSCRIBED,
    UNSUBSCRIBE,
    USE,
    CREATE,
    LIST,
    INFO
};

typedef struct sock_addrs {
    struct sockaddr_in client;
    struct timeval timeout;
    int server_fd;
    int status;
    char *pathname;
    fd_set rfds;
    fd_set wfds;
    fd_set efds;
} sock_addrs_t;

typedef struct client {
    sock_addrs_t addrs;
    int (*cmd[TOTAL_CMD])(struct client* client, char** param);
} client_t;

int error_handling(int ac, char **av);

// client.c
int run_client(char *ip, int port);

// init.c
int init_client(client_t *client, char *ip, int port);

int read_client_cli(client_t *client);

// utils.c
char *removing_line_break(char *str);
int get_cmd_pos(char *str);
int str_to_array(char ***array, char *str, char *sep);

// Commands
int show_help(client_t *client, char **params);

int user_login(client_t *client, char **param);
int user_logout(client_t *client, char **param);

int send_message(client_t *client, char **param);
int list_messages(client_t *client, char **param);

int get_users(client_t *client, char **params);
int get_user(client_t *client, char **params);

int do_nothing(client_t *client, char **param);

int subscribe_client(client_t *client, char **param);
int list_subscribed(client_t *client, char **param);
int unsubscribe_client(client_t *client, char **param);

int set_command(client_t *client, char **param);

int list_sub_res(client_t *client, char **param);

int info_current_res(client_t *client, char **param);

int create_sub_res(client_t *client, char **param);

#endif /* !CLIENT_H_ */
