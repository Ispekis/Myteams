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
    #include <fcntl.h>
    #define TOTAL_CMD 15
    #define MAX_CONNECTIONS 100
    #define TOTAL_TEAM 10
    #define TOTAL_MEMBER 100
    #define MAX_SIZE_NAME 255
    #define MAX_DESCRIPTION_LENGTH 255
    #define USER_LOGING 0
    #define USER_CREATE 1

static const char *CMD_LIB[] = {"help", "login", "logout", "users", "user",
"send", "messages", "subscribe", "subscribed", "unsubscribe", "use", "create",
"list", "info", NULL};

static const char *save_file_name = "server.data";

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

typedef struct messages_s {
    uuid_t sender_uuid;
    uuid_t dest_uuid;
    char message[MAX_BODY_LENGTH];
    time_t timestamp;
} __attribute__((packed)) messages_t;

typedef struct user {
    char name[MAX_NAME_LENGTH];
    uuid_t uuid;
    bool is_logged;
    int current_fd;
    int context;
    uuid_t *teams_uuid;
    int nbr_teams;
    messages_t *messages;
    int nbr_messages;
} __attribute__((packed)) user_t;

typedef struct reply_s {
    char body[MAX_BODY_LENGTH];
    uuid_t user_uuid;
    time_t timestamp;
} __attribute__((packed)) reply_t;

typedef struct thread {
    uuid_t channel_uuid;
    uuid_t thread_uuid;
    uuid_t user_uuid;
    char thread_title[MAX_NAME_LENGTH];
    char thread_body[MAX_BODY_LENGTH];
    time_t timestamp;
    reply_t *replies;
    int nbr_replies;
} __attribute__((packed)) thread_t;

typedef struct channel {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    uuid_t uuid;
    size_t member_nbr;
    thread_t *threads;
    int nbr_thread;
} __attribute__((packed)) channel_t;

typedef struct teams {
    uuid_t teams_uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    size_t subs_nbr;
    uuid_t *members_uuid;
    channel_t *channel;
    int nbr_channel;
} __attribute__((packed)) teams_t;

typedef struct data {
    user_t *users;
    int nbr_users;
    teams_t *teams;
    int nbr_teams;
} data_t;

typedef struct server {
    sock_addrs_t addrs;
    data_t data;
    struct signalfd_siginfo fdsi;
    int sfd;
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
int receive_subscribe(server_t *server, int index, client_packet recv_data);
int receive_list_teams(server_t *server, int index, client_packet recv_data);
int receive_unsubscribe(server_t *server, int index, client_packet recv_data);
int receive_use(server_t *server, int index, client_packet recv_data);
int receive_info(server_t *server, int index, client_packet recv_data);
int receive_subscribed(server_t *server, int index, client_packet recv_data);
int receive_create(server_t *server, int index, client_packet recv_data);

// Usable in multiple file
int join_teams(teams_t *team, uuid_t user_uuid);
int member_add_team(user_t *user, uuid_t team_uuid);
int receive_list_teams(server_t *server, int index, client_packet recv_data);
int receive_messages(server_t *server, int index, client_packet recv_data);

// save_backup
int catch_shutdown(server_t server);
void load_save(server_t *server);

// Index getters
channel_t *index_of_channel(data_t *data, client_packet recv_data);
thread_t *index_of_thread(data_t *data, client_packet recv_data);
teams_t *index_of_team(data_t *data, client_packet recv_data);
user_t *index_of_user(data_t *data, uuid_t user_uuid);

// Savers
void save_users(data_t data, int fd);
void save_teams(data_t data, int fd);

// Loaders
void load_users(data_t *data, int fd);
void load_teams(data_t *data, int fd);

// info function switch
void info_team(data_t data, int client_fd, client_packet recv_data);
void info_channel(data_t data, int client_fd, client_packet recv_data);
void info_thread(data_t data, int client_fd, client_packet recv_data);

// list function switch
void list_team(data_t data, int client_fd, client_packet recv_data);
void list_channel(data_t data, int client_fd, client_packet recv_data);
void list_thread(data_t data, int client_fd, client_packet recv_data);
void list_reply(data_t data, int client_fd, client_packet recv_data);

// create functions switch
int receive_teams(data_t *data, int client_fd, client_packet recv_data);
int receive_channel(data_t *data, int client_fd, client_packet recv_data);
int create_thread(data_t *data, int client_fd, client_packet recv_data);
int create_reply(data_t *data, int client_fd, client_packet recv_data);

// Subscribed
void list_subscribed_team(data_t data, user_t user, int client_fd);
void list_subscribed_user(data_t data, teams_t team, int client_fd);

#endif /* !SERVER_H_ */
