/*
** EPITECH PROJECT, 2023
** B-NWP-400-PAR-4-1-myteams-jeras.bertine
** File description:
** error_handler
*/

#include "server.h"

int is_all_digits(char *str)
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
    if (ac != 2)
        return 1;
    if (is_all_digits(av[1]) == 1) {
        dprintf(STDERR_FILENO, "'%s' is not a valid port number\n", av[1]);
        return 1;
    }
    return 0;
}
