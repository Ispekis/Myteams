##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

CLIENT_PATH	=	src/client

SERVER_PATH	=	src/server

TEST_FILES	=	tests/test_project.c

TEST_NAME	=	unit_tests

all:
	$(MAKE) -C $(CLIENT_PATH)
	$(MAKE) -C $(SERVER_PATH)

tests_run:
	$(CC) $(TEST_FILES) -o $(TEST_NAME) -lcriterion --coverage
	./${TEST_NAME}
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

clean:
	$(MAKE) clean -C $(CLIENT_PATH)
	$(MAKE) clean -C $(SERVER_PATH)

fclean:	clean
	$(MAKE) fclean -C $(CLIENT_PATH)
	$(MAKE) fclean -C $(SERVER_PATH)

re:	fclean all

.PHONY: all clean fclean re tests_run
