##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for menger
##

CC	=	gcc

CFLAGS	=	-I./include -Wall -Wextra -fpic

SRC	=	src/my_malloc.c		\
		src/push_memory.c	\
		src/malloc_init.c	\
		src/printbase.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy_malloc.so

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(CFLAGS)
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all