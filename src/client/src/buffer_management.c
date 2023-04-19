/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** buffer_management
*/

#include "client.h"

static int nbr_space(char *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == ' ') {
            count++;
        } else {
            break;
        }
    return count;
}

char *get_cmd(char **str)
{
    char *cmd = NULL;
    int index;
    char *index_str = strchr((*str), ' ');

    if (index_str == NULL)
        return NULL;
    index = (int) (index_str - (*str));
    cmd = malloc(sizeof(char) * index + 1);
    strncpy(cmd, (*str), index);
    cmd[index] = '\0';
    (*str) += index;
    (*str) += nbr_space(*str);
    return cmd;
}

static char* get_param(char **str)
{
    char *param;
    char *index_str;
    int index;

    if ((*str)[0] != '"')
        return NULL;
    (*str)++;
    index_str = strchr((*str), '"');
    if (index_str == NULL)
        return NULL;
    index = (int) (index_str - (*str));
    param = malloc(sizeof(char) * (index + 1));
    strncpy(param, (*str), index);
    param[index] = '\0';
    (*str) += (index) + 1;
    (*str) += nbr_space(*str);
    return param;
}

int nbr_params(char *input)
{
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++)
        if (input[i] == '"')
            count++;
    if (count % 2 == 1) {
        return -1;
    }
    return count / 2;
}

char **get_params(char *input)
{
    int nbr = nbr_params(input);
    char **arr;
    char *tmp = NULL;

    if (nbr == -1)
        return NULL;
    arr = malloc(sizeof(char*) * (nbr  + 1));
    for (int i = 0; input[0] != '\0'; i++) {
        tmp = get_param(&input);
        if (tmp == NULL)
            return NULL;
        arr[i] = strdup(tmp);
    }
    arr[nbr] = NULL;
    return arr;
}
