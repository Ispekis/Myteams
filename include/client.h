/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include "../libs/myteams/logging_client.h"
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

typedef struct context_type_s {
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
} context_type_t;

typedef struct data_s {
    bool is_logged;
    char user_name[MAX_NAME_LENGTH];
    uuid_t user_uuid;
    int context;
    context_type_t context_type;
} data_t;

typedef struct client {
    sock_addrs_t addrs;
    data_t data;
    int (*cmd[TOTAL_CMD])(struct client* client, char** param);
    int (*receive[TOTAL_TYPE])(struct client* client, server_packet recv_data);
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
void print_code_res(code_t code);

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

int use_command(client_t *client, char **param);

int list_sub_res(client_t *client, char **param);
int list_all_teams(client_t *client, char **param);

int info_current_res(client_t *client, char **param);

int create_sub_res(client_t *client, char **param);

// Create senders
void send_thread_packet(client_packet *packet, data_t data, char **param);
void send_team_packet(client_packet *packet, data_t data, char **param);
void send_reply_packet(client_packet *packet, data_t data, char **param);
void send_channel_packet(client_packet *packet, data_t data, char **param);

int read_server(client_t *client);

int recv_login(client_t *client, server_packet recv_data);

int recv_logout(client_t *client, server_packet recv_data);

int recv_send(client_t *client, server_packet recv_data);

int recv_user(client_t *client, server_packet recv_data);

int recv_users(client_t *client, server_packet recv_data);

int recv_subscribe(client_t *client, server_packet recv_data);

int recv_list_teams(client_t *client, server_packet recv_data);

int recv_unsubscribe(client_t *client, server_packet recv_data);

int recv_use(client_t *client, server_packet recv_data);

int recv_messages(client_t *client, server_packet recv_data);

int recv_info(client_t *client, server_packet recv_data);

int recv_subscribed(client_t *client, server_packet recv_data);

int recv_create(client_t *client, server_packet recv_data);

// switch create function
int recv_create_team(data_t *data, server_packet recv_data);


// Buffer management
char **get_params(char *input);
int nbr_params(char *input);
char *get_cmd(char **str);

#endif /* !CLIENT_H_ */
