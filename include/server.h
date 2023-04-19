/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #include "../libs/myteams/logging_server.h"
    #include "../libs/myteams/logging_client.h"
    #include "shared.h"
    #define TOTAL_CMD 15
    #define MAX_CONNECTIONS 100
    #define TOTAL_TEAM 10
    #define TOTAL_MEMBER 100
    #define MAX_SIZE_NAME 255
    #define MAX_DESCRIPTION_LENGTH 255

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
    bool is_logged;
    int current_fd;
    char **subbed_teams;
    int nbr_teams;
} user_t;

typedef struct teams {
    uuid_t teams_uuid;
    char *name;
    char description[MAX_DESCRIPTION_LENGTH];
    size_t subs_nbr;
    char **team_member;
} teams_t;

typedef struct channel {
    char *name;
    uuid_t uuid;
    size_t member_nbr;
} channel_t;

typedef struct thread {
    uuid_t message_uuid;
    uuid_t thread_uuid;
} thread_t;

typedef struct data {
    user_t *users;
    int nbr_users;
    channel_t *channel;
    int nbr_channel;
    teams_t *teams;
    int nbr_teams;
} data_t;

typedef struct server {
    sock_addrs_t addrs;
    data_t data;
    int (*cmd[TOTAL_CMD])(struct server* server, char** param, int index);
    int (*receive[TOTAL_TYPE])(struct server* server,
    int index, client_packet recv_data);
} server_t;

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
int receive_send(server_t *server, int index, client_packet recv_data);
int receive_users(server_t *server, int index, client_packet recv_data);
int receive_user(server_t *server, int index, client_packet recv_data);
int receive_teams(server_t *server, int index, client_packet recv_data);

#endif /* !SERVER_H_ */
