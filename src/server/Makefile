##
## EPITECH PROJECT, 2023
## B-NWP-400-PAR-4-1-myteams-jeras.bertine
## File description:
## Makefile
##

PATH_TO_ROOT	=	../..

SRC	=	src/main.c								\
		src/error_handler.c						\
		src/server.c							\
		src/init.c								\
		src/client_management.c					\
		src/utils.c								\
		src/receiver/login.c					\
		src/receiver/logout.c					\
		src/receiver/send.c						\
		src/receiver/user.c						\
		src/receiver/teams.c					\
		src/receiver/list.c						\
		src/receiver/subscribe.c				\
		src/receiver/unsubscribe.c				\
		src/receiver/use.c						\
		src/receiver/messages.c					\
		src/save_backup.c						\
		src/load/load_users.c					\
		src/save/save_users.c					\
		src/receiver/info.c						\
		src/receiver/info_context.c				\
		src/receiver/subscribed.c				\
		src/receiver/create.c					\
		src/receiver/create_thread.c			\
		src/receiver/create_reply.c				\
		src/index_threads.c						\
		src/receiver/create_channel.c			\
		src/receiver/subscribed_users.c			\
		src/receiver/subscribed_teams.c			\
		src/save/save_teams.c					\
		src/load/load_teams.c					\
		src/receiver/list_context.c				\

NAME	=	myteams_server

OBJ	=	$(SRC:.c=.o)

CPPFLAGS	=	-I../../include

LDFLAGS		=	-L../../libs/myteams -lmyteams -luuid

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)
	mv $(NAME) $(PATH_TO_ROOT)

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean:	clean
	$(RM) $(PATH_TO_ROOT)/$(NAME)

re:	fclean all

debug: CPPFLAGS += -g3
debug: re

.PHONY: all clean fclean re
