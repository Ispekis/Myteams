/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myftp-vincent.shao
** File description:
** informational_cmd
*/

#include "client.h"

int show_help(client_t *client, char **params)
{
    printf("Available commands :\n");
    printf("help login logout users send messages subscribe\n");
    printf("subscribed unsubscribe use create list info\n");
    return 0;
}

int get_users(client_t *client, char **params)
{
    return 0;
}

int get_user(client_t *client, char **params)
{
    return 0;
}
