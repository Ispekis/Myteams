##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SERVER_PATH	=	src/server

CLIENT_PATH	=	src/client

SERVER_SRC	=	$(SERVER_PATH)/main.c	\
				$(SERVER_PATH)/error_handler.c

CLIENT_SRC	=	$(CLIENT_PATH)/main.c	\
				$(CLIENT_PATH)/error_handler.c

TEST_FILES	=	tests/test_project.c

SERVER_NAME	=	myteams_server

CLIENT_NAME	=	myteams_cli

CPPFLAGS	=	-I./include

TEST_NAME	=	unit_tests

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)

CPPFLAGS	=	-I./include

all:	$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME):	$(SERVER_OBJ)
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJ) $(CPPFLAGS)

$(CLIENT_NAME):	$(CLIENT_OBJ)
	$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(CPPFLAGS)

tests_run:
	$(CC) $(TEST_FILES) -o $(TEST_NAME) -lcriterion --coverage
	./${TEST_NAME}
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

clean:
	$(RM) $(SERVER_OBJ)
	$(RM) $(CLIENT_OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean:	clean
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)
	$(RM) $(TEST_NAME)

re:	fclean all

.PHONY: all clean fclean re tests_run
