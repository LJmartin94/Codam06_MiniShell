# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: limartin <limartin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/14 11:19:17 by limartin      #+#    #+#                  #
#    Updated: 2020/10/31 16:22:32 by limartin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./srcs/

PARSE_PATH = parse/

EX_PATH = execute/

INCL_PATH = ./includes/

LIBFT_PATH = ./libft

CC = gcc

#TODO remove sanitise flag when submitting
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

HEADER_FILES = $(INCL_PATH)

#Source files mandatory part
SRC = $(SRC_PATH)main.c \
	$(SRC_PATH)error.c \
	$(SRC_PATH)invalid.c \
	$(SRC_PATH)$(PARSE_PATH)parse_input.c \
	$(SRC_PATH)$(PARSE_PATH)tokenizer.c \
	$(SRC_PATH)$(PARSE_PATH)tokenizer_utils.c \
	$(SRC_PATH)$(PARSE_PATH)fsm.c \
	$(SRC_PATH)$(PARSE_PATH)control_states.c \
	$(SRC_PATH)$(PARSE_PATH)basic_states.c \
	$(SRC_PATH)$(PARSE_PATH)dq_basic_states.c \
	$(SRC_PATH)$(PARSE_PATH)dq_exit_basic_states.c \
	$(SRC_PATH)$(PARSE_PATH)sq_basic_states.c \
	$(SRC_PATH)$(PARSE_PATH)sq_exit_basic_states.c \
	$(SRC_PATH)$(PARSE_PATH)recognise_token_state.c \
	$(SRC_PATH)$(PARSE_PATH)validate_option_flags.c \
	$(SRC_PATH)$(PARSE_PATH)comp_links.c \
	$(SRC_PATH)$(PARSE_PATH)free_and_exit.c \
	$(SRC_PATH)$(EX_PATH)execute.c \
	$(SRC_PATH)$(EX_PATH)echo.c \
	$(SRC_PATH)$(EX_PATH)env.c \
	$(SRC_PATH)$(EX_PATH)env_utils.c \
	$(SRC_PATH)$(EX_PATH)env_free.c \
	$(SRC_PATH)$(EX_PATH)export.c \
	$(SRC_PATH)$(EX_PATH)unset.c \
	$(SRC_PATH)$(EX_PATH)pwd.c \
	$(SRC_PATH)$(EX_PATH)cd.c \

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
