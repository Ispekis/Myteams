##
## EPITECH PROJECT, 2023
## B-NWP-400-PAR-4-1-myteams-jeras.bertine
## File description:
## Makefile
##

SRC	=	src/main.c							\
		src/error_handler.c					\
		src/server.c							\
		src/init.c							\
		src/client_management.c				\
		src/cli_management.c					\
		src/utils.c							\
		src/commands/authentification_cmd.c	\
		src/commands/communication_cmd.c		\
		src/commands/informational_cmd.c		\
		src/commands/miscellaneous_cmd.c		\
		src/commands/subscription_cmd.c		\
		src/commands/use_cmd.c				\
		src/commands/create_cmd.c			\
		src/commands/list_cmd.c				\
		src/commands/info_cmd.c

NAME	=	myteams_server

OBJ	=	$(SRC:.c=.o)

CPPFLAGS	=	-I../../include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)
	mv $(NAME) ../..

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
