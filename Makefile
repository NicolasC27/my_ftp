##
## Makefile for Makefile in /home/cheval_8/rendu/CPE_2015_Allum1
##
## Made by Nicolas Chevalier
## Login   <cheval_8@epitech.net>
##
## Started on  Mon Feb  8 14:58:11 2016 Nicolas Chevalier
## Last update Sun May 21 21:50:09 2017 Nicolas
##


NAME		= server

SRC		= srv/actions.c \
		  srv/authentification.c \
		  srv/client.c \
		  srv/commands.c \
		  srv/execute.c \
		  srv/ftp.c \
		  srv/init.c \
		  srv/main.c \
		  srv/manage_input.c \
		  srv/move.c \
		  srv/rfc.c \
		  srv/strtolower.c \
		  srv/transfert.c \
		  srv/download.c \
		  srv/wait.c \
		  srv/upload.c

MOD		= $(SRC:.c=.o)


CFLAGS		= -Iincludes/
CFLAGS		+= -W -Wall -Werror

all:		$(NAME)

$(NAME):	$(MOD)
		gcc -g $(MOD) -o $(NAME) $(LDFLAGS)

clean		:
		 rm -rf $(MOD)

fclean		: clean
		  rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
