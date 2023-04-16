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
    #define TOTAL_TYPE 2
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

enum PACKET_TYPE {
    TYPE_LOGIN,
    TYPE_LOGOUT
};

typedef struct server_packet {
    int type;
    uuid_t user_uuid;
    int user_name_len;
    char user_name[MAX_NAME_LENGTH];
} __attribute__((packed)) server_packet;

typedef struct client_packet {
    int type;
    char user_name[MAX_NAME_LENGTH];
    int name_len;
    uuid_t user_uuid;
} __attribute__((packed)) client_packet;

#endif /* !SHARED_H_ */
