# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/14 11:19:17 by limartin      #+#    #+#                  #
#    Updated: 2020/10/14 14:19:26 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./srcs/

INCL_PATH = ./incl/

LIBFT_PATH = ./libft/

CC = gcc

#TODO remove sanitise flag when submitting
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

HEADER_FILES = $(INCL_PATH)

#Source files mandatory part
SRC = $(SRC_PATH)

#Source files bonus part
SRC_B = $(SRC_PATH)

#Object files
OBJ := ${SRC:%.c=%.o}

BOBJ := ${SRC_B:%.c=%.o}

#Avoid relinking bonus
ifdef WITH_BONUS
COMPILE_OBJECTS = $(OBJ) $(BOBJ)
else
COMPILE_OBJECTS = $(OBJ)
endif

#TODO specifying OS may not be necessary
#Specify OS (Mac default)
ifdef FOR_LINUX
OS_FLAG = LINUX=1
endif

ifndef FOR_LINUX
OS_FLAG = MAC=1
endif

all: $(NAME)

$(NAME): $(COMPILE_OBJECTS)
	$(CC) -o $(NAME) $(COMPILE_OBJECTS) $(CFLAGS) -D $(OS_FLAG) -L$(LIBFT_PATH)
	

%.o: %.c $(HEADER_FILES) $(LIBFT)
	$(CC) -o $@ -c $< $(CFLAGS) -O3 -I $(INCL_PATH) -I $(LIBFT_PATH) -D $(OS_FLAG)

$(LIBFT):
 	@make -C $(LIBFT)

bonus:
	@ $(MAKE) WITH_BONUS=1 all

clean:
	@make clean -C $(LIBFT_PATH)
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all

linux:
	@ $(MAKE) FOR_LINUX=1 all

linuxbonus:
	@ $(MAKE) WITH_BONUS=1 linux

linuxre: fclean linux

.PHONY: all bonus clean fclean re linux linuxbonus linuxre 
