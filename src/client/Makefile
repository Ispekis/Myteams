##
## EPITECH PROJECT, 2023
## B-NWP-400-PAR-4-1-myteams-jeras.bertine
## File description:
## Makefile
##

SRC	=	src/main.c				\
		src/error_handler.c		\
		src/client.c			\
		src/init.c

NAME	=	myteams_cli

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
