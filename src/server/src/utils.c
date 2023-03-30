/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** utils
*/

#include "server.h"

char *removing_line_break(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\r') {
            str[i] = '\0';
        }
    }
    return str;
}

int get_cmd_pos(char *str)
{
    for (int i = 0; CMD_LIB[i] != NULL; i++) {
        if (strcmp(str, CMD_LIB[i]) == 0) {
            return i;
        }
    }
    return -1;
}

static int get_array_length(char *str, char *sep)
{
    char *strToken = strtok(str, sep);
    int count = 0;

    while (strToken != NULL) {
        count++;
        strToken = strtok(NULL, sep);
    }
    return count;
}

int str_to_array(char ***array, char *str, char *sep)
{
    char *tmp = strdup(str);
    int len = get_array_length(tmp, sep);
    char *strToken = strtok(str, sep);
    int index = 0;

    *array = malloc(sizeof(char*) * len + 1);
    while (strToken != NULL) {
        (*array)[index] = strdup(strToken);
        index++;
        strToken = strtok(NULL, sep);
    }
    (*array)[index] = NULL;
    return len;
}

void reply_format(int fd, code_t code)
{
    dprintf(fd, "%i %s\n", code.code, code.msg);
}
