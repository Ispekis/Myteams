/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** shared
*/

#ifndef SHARED_H_
    #define SHARED_H_
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
    #include <dlfcn.h>
    #include <uuid/uuid.h>
    #include <time.h>
    #define TOTAL_TYPE 12
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define MAX_MESSAGE_LENGTH 255
    #define MAX_UUID_LENGTH 37

enum PACKET_TYPE {
    TYPE_LOGIN,
    TYPE_LOGOUT,
    TYPE_SEND,
    TYPE_USER,
    TYPE_USERS,
    TYPE_CREATE_TEAM,
    TYPE_SUBSCRIBE,
    TYPE_LIST,
    TYPE_UNSUBSCRIBE,
    TYPE_USE,
    TYPE_MESSAGES,
    TYPE_SUBSCRIBED,
    TYPE_INFO,
    TYPE_CREATE_CHANNEL,
    TYPE_CREATE_THREAD,
    TYPE_CREATE_REPLY
};

enum CONTEXT {
    DEFAULT_CONTEXT,
    TEAM_CONTEXT,
    CHANNEL_CONTEXT,
    THREAD_CONTEXT,
};

typedef struct codes_s {
    int code;
    char *msg;
} code_t;

static const code_t CODE_120 = {200, "Service conncted to server"};
static const code_t CODE_200 = {200, "Action successfully completed"};
static const code_t CODE_214 = {214, "Showing help message"};
static const code_t CODE_400 = {400, "Bad Request"};
static const code_t CODE_403 = {403, "Action not permitted"};
static const code_t CODE_404 = {404, "Resource not found"};
static const code_t CODE_500 = {500, "Internal Server Error"};

typedef struct server_packet {
    code_t code;
    int type;
    int user_name_len;
    int message_len;
    int status;
    int context;
    char name[MAX_NAME_LENGTH];
    char message[MAX_MESSAGE_LENGTH];
    char description[MAX_MESSAGE_LENGTH];
    char team_name[MAX_NAME_LENGTH];
    uuid_t user_uuid;
    uuid_t dest_uuid;
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
    uuid_t use_uuid;
    uuid_t send_uuid;
    int nbr_messages;
} __attribute__((packed)) server_packet;

typedef struct client_packet {
    int type;
    int name_len;
    int message_len;
    int status;
    int context;
    char name[MAX_NAME_LENGTH];
    char message[MAX_MESSAGE_LENGTH];
    char description[MAX_MESSAGE_LENGTH];
    char team_name[MAX_NAME_LENGTH];
    uuid_t user_uuid;
    uuid_t dest_uuid;
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
    uuid_t use_uuid;
    uuid_t send_uuid;
} __attribute__((packed)) client_packet;

#endif /* !SHARED_H_ */
