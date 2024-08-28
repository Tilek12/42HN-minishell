# ANSI color codes
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g
RM		:= rm -rf

LIBFT_PATH  := ./libft
OBJ_PATH	:= ./obj
P_SRC_PATH	:= ./p_srcs
E_SRC_PATH	:= ./e_srcs
MAIN		:= main.c
SRC_FILES	:= ./p_srcs/signals.c\
				./p_srcs/errors.c \
				./p_srcs/tokenization/t_tokenize.c \
				./p_srcs/tokenization/t_add_tokens.c \
				./p_srcs/tokenization/t_utils.c \
				./p_srcs/parsing/parse.c \
				./p_srcs/parsing/parse_utils.c \
				./p_srcs/expanding/expanding.c \
				./p_srcs/expanding/expanding_1.c \
				./p_srcs/expanding/expanding_2.c \
				./p_srcs/expanding/expanding_3.c \
				./p_srcs/expanding/expand_quote_check.c \
				./p_srcs/expand_heredoc/expand_heredoc.c \
				./p_srcs/expand_heredoc/expand_utils_1.c \
				./p_srcs/expand_heredoc/expand_utils_2.c \
				./p_srcs/quote_handling/quote_handling.c \
				./p_srcs/quote_handling/d_quote_handler.c \
				./p_srcs/quote_handling/s_quote_handler.c \
				./e_srcs/custom_functions/custom_functions.c \
				./e_srcs/custom_functions/split_str.c \
				./e_srcs/array/array_handler.c \
				./e_srcs/environment/env_set.c \
				./e_srcs/environment/env_sort.c \
				./e_srcs/environment/env_value.c \
				./e_srcs/custom_functions/custom_functions.c \
				./e_srcs/environment/env_var.c \
				./e_srcs/list_handler/command_list_utils.c \
				./e_srcs/list_handler/command_list.c \
				./e_srcs/list_handler/redirection_checker.c \
				./e_srcs/list_handler/redirection_list_utils.c \
				./e_srcs/list_handler/redirection_list.c \
				./e_srcs/builtins/builtin_checker.c \
				./e_srcs/builtins/cd.c \
				./e_srcs/builtins/cd_utils.c \
				./e_srcs/builtins/echo.c \
				./e_srcs/builtins/env.c \
				./e_srcs/builtins/exit.c \
				./e_srcs/builtins/export.c \
				./e_srcs/builtins/export_utils.c \
				./e_srcs/builtins/pwd.c \
				./e_srcs/builtins/unset.c \
				./e_srcs/cleanup/cleanup.c \
				./e_srcs/cleanup/error.c \
				./e_srcs/cleanup/free.c \
				./e_srcs/heredoc/heredoc.c \
				./e_srcs/redirection/redirection.c \
				./e_srcs/execution/execute_utils.c \
				./e_srcs/execution/execute_checker.c \
				./e_srcs/execution/execute_process.c \
				./e_srcs/execution/execute_fd_handler.c \
				./e_srcs/execution/execute.c

OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES:.c=.o))
MAIN_OBJ	:= $(OBJ_PATH)/main.o

LIBFT		:= $(LIBFT_PATH)/libft.a

all: update $(NAME)

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE COMMAND IN MAC
rl:
	@brew install readline

#IF SUBMODULE IS NOT EXISTS IN THE REPO, FETCH AND UPDATE
update:
	@git submodule update --init --recursive > /dev/null 2>&1
	@git submodule update --remote --merge > /dev/null 2>&1
	@echo "$(GREEN)libft connected.$(RESET)"

#IF READLINE IS NOT INSTALLED INSTALL IT WITH MAKE LINUX (LINUX ONLY)
linux: update readline_linux_install $(NAME)

#COMMAND TO INSTALL READLINE ON LINUX
readline_linux_install:
	@sudo apt install libreadline-dev

$(NAME): $(MAIN_OBJ) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline
	@echo "$(GREEN)minishell created.$(RESET)"

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(P_SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo "$(MAGENTA)minishell object files cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo "$(MAGENTA)minishell removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re git_sub_update
