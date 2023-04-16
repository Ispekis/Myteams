/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include "../libs/myteams/logging_server.h"
    #include "shared.h"
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

typedef struct user {
    char *name;
    uuid_t uuid;
} user_t;

typedef struct data {
    user_t *users;
    int nbr_users;
} data_t;

typedef struct server {
    sock_addrs_t addrs;
    data_t data;
    int (*cmd[TOTAL_CMD])(struct server* server, char** param, int index);
    int (*receive[TOTAL_TYPE])(struct server* server, int index, client_packet recv_data);
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
char *removing_line_break(char *str);
int str_to_array(char ***array, char *str, char *sep);
void reply_format(int fd, code_t code);

// Receiver
int receive_login(server_t *server, int index, client_packet recv_data);
int receive_logout(server_t *server, int index, client_packet recv_data);

#endif /* !SERVER_H_ */
