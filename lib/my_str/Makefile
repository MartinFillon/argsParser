##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## the makefile for my_str
##

CC	=	gcc
RM	=	rm -f

INCLUDE	=	-I../../include


SRC	=	./add.c 		\
		./case.c 		\
		./checks.c 		\
		./compare.c		\
		./content.c 	\
		./convert.c 	\
		./format.c 		\
		./from.c 		\
		./create.c 		\
		./join.c 		\
		./modify.c 		\
		./print.c 		\
		./split.c 		\
		./trim.c 		\
		./utils.c 		\

CFLAGS += -Werror -Wextra -Wall
CPPFLAGS += $(INCLUDE)

ifeq ($(DEBUG),1)
	CFLAGS += -g3
endif

OBJ	=	$(SRC:.c=.o)

NAME	=	../libmy.a

all:	$(OBJ)
	@ar cq $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean

re:	fclean all

.PHONY: all clean re
