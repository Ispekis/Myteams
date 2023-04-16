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

enum PACKET_TYPE {
    TYPE_LOGIN,
    TYPE_LOGOUT
};

typedef struct server_packet {
    int type;
    int user_uuid_len;
    char *user_uuid;
    int user_name_len;
    char *user_name;
} __attribute__((packed)) server_packet;


#endif /* !SHARED_H_ */
