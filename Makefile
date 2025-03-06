# colors
GREEN  := \033[32m
GREEN_BG := \033[42m
BOLD := \033[1m
PURPLE := \033[35m
RESET  := \033[0m


NAME := pipex
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -I./include -I./libft
OBJ_DIR := obj
SRCS := src/pipex.c src/check_path.c src/utils.c

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
RM := rm -rf

all: libft $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) all

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME)$(RESET)$(GREEN) created!$(RESET)"

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(sort $(dir $(OBJS)))

clean:
	$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(PURPLE)$(BOLD)$(NAME)$(RESET)$(PURPLE) object files removed!$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(PURPLE)$(BOLD)$(NAME)$(RESET)$(PURPLE) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re