/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
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

typedef struct client_s {
    int fd;
    bool is_logged;
    bool is_anonyme;
    int ambivalence;
    struct sockaddr_in data_socket;
    struct sockaddr_in data_client;
    int data_fd;
    char *pathname;
} client_t;

typedef struct sock_addrs {
    struct sockaddr_in server;
    struct timeval timeout;
    int socket_fd;
    int name;
    int status;
    char *pathname;
    fd_set rfds;
    client_t clients[MAX_CONNECTIONS];
} sock_addrs_t;

typedef struct server {
    sock_addrs_t addrs;
    int (*cmd[TOTAL_CMD])(struct server* server, char** param, int index);
} server_t;

typedef struct codes_s {
    int code;
    char *msg;
} code_t;

static const code_t C214 = {214, "Help message"};

int error_handling(int ac, char **av);
int run_server(int port);
int init_server(server_t *server, int port);
void accept_client_to_server(sock_addrs_t *addrs);
void read_from_client(server_t *server, int index);
int get_cmd_pos(char *str);
int get_cli_events(server_t *server, char* input, int index);
char *removing_line_break(char *str);
int str_to_array(char ***array, char *str, char *sep);
void reply_format(int fd, code_t code);

// Commands

int show_help(server_t *server, char **params, int index);

int user_login(server_t *server, char **param, int index);
int user_logout(server_t *server, char **param, int index);

int send_message(server_t *server, char **param, int index);
int list_messages(server_t *server, char **param, int index);

int get_users(server_t *server, char **params, int index);
int get_user(server_t *server, char **params, int index);

int do_nothing(server_t *server, char **param, int index);

int subscribe_client(server_t *server, char **param, int index);
int list_subscribed(server_t *server, char **param, int index);
int unsubscribe_client(server_t *server, char **param, int index);

#endif /* !SERVER_H_ */
