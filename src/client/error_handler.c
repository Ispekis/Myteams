/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** error_handler
*/

#include "client.h"

int isAllDigits(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int error_handling(int ac, char **av)
{
    if (ac != 3)
        return 1;
    if (isAllDigits(av[2]) == 1) {
        dprintf(STDERR_FILENO, "'%s' is not a valid port number\n", av[2]);
        return 1;
    }
    return 0;
}