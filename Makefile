# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/14 11:19:17 by limartin      #+#    #+#                  #
#    Updated: 2020/10/27 10:43:45 by jsaariko      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./srcs/

INCL_PATH = ./includes/

LIBFT_PATH = ./libft

CC = gcc

#TODO remove sanitise flag when submitting
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

HEADER_FILES = $(INCL_PATH)

#Source files mandatory part
SRC = $(SRC_PATH)main.c \
	$(SRC_PATH)parse_input.c \
	$(SRC_PATH)tokenizer.c \
	$(SRC_PATH)tokenizer_utils.c \
	$(SRC_PATH)error.c \
	$(SRC_PATH)invalid.c \
	$(SRC_PATH)fsm.c \
	$(SRC_PATH)entry_error_exit_state.c \
	$(SRC_PATH)cmd_opt_arg_sep_state.c \
	$(SRC_PATH)recognise_token_state.c \
	$(SRC_PATH)comp_links.c \
	$(SRC_PATH)free_and_exit.c \
	$(SRC_PATH)execute.c \
	$(SRC_PATH)env.c \
	$(SRC_PATH)export.c \
	$(SRC_PATH)unset.c \
	$(SRC_PATH)echo.c \

#Source files bonus part
SRC_B = # $(SRC_PATH) bonus_goes_here.c #TODO

#Object files
OBJ := ${SRC:%.c=%.o}

#Bonus object files
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
	@make -C $(LIBFT_PATH)
	@$(CC) -o $(NAME) $(COMPILE_OBJECTS) $(CFLAGS) -D $(OS_FLAG) \
	-L$(LIBFT_PATH) -lft
	@echo "Minishell compiled"

%.o: %.c $(HEADER_FILES)
	@$(CC) -o $@ -c $< $(CFLAGS) -O3 -I $(INCL_PATH) -I $(LIBFT_PATH) \
	-D $(OS_FLAG)

bonus:
	@$(MAKE) WITH_BONUS=1 all
	@echo "...but done ✨fancy✨"

clean:
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(OBJ) $(BOBJ)
	@echo "Minishell object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "Minishell fully cleaned"

re: fclean all

linux:
	@$(MAKE) FOR_LINUX=1 all
	@echo "Compiled for Linux 🐧"

linux_bonus:
	@ $(MAKE) WITH_BONUS=1 linux
	@echo "...but done ✨fancy✨"

linux_re: fclean linux

.PHONY: all bonus clean fclean re linux linux_bonus linux_re
