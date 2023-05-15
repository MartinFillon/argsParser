##
## EPITECH PROJECT, 2023
## Corewar
## File description:
## Makefile for corewar
##

CC	=	gcc

SRC = 	src/main.c

NAME = argsParser

OBJ = $(SRC:.c=.o)

CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	-Iinclude
LDFLAGS		+=	-Llib
LDLIBS		+=	-lmy

ifeq ($(DEBUG),1)
	CC = clang
	CFLAGS += -g3 -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

OBJ = $(SRC:.c=.o)

all: lib $(NAME)

lib:
	$(MAKE) -C ./lib

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./lib clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C ./lib fclean

re: fclean all

.PHONY: all clean fclean re lib
