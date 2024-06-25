# Compiler and flags
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

# Name of the library
NAME = minishell

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c

PAR_DIR = parsing
PAR_SRC = $(PAR_DIR)/token.c $(PAR_DIR)/create_list.c $(PAR_DIR)/expand.c

TOOL_DIR = tools
TOOL_SRC = $(TOOL_DIR)/utils.c $(TOOL_DIR)/free_memory.c $(TOOL_DIR)/allocate_memory.c

BUILD_DIR = buildin
BUILD_SRC = $(BUILD_DIR)/cd.c $(BUILD_DIR)/echo.c $(BUILD_DIR)/pwd.c $(BUILD_DIR)/export.c \
			$(BUILD_DIR)/env.c $(BUILD_DIR)/unset.c $(BUILD_DIR)/exit.c $(BUILD_DIR)/utils.c

LIBFT_DIR = libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)

EXC_DIR = execute
EXC_SRC = $(EXC_DIR)/execution.c  $(EXC_DIR)/ft_split_simple.c  $(EXC_DIR)/execute_utilis.c \
		$(EXC_DIR)/set_redirections.c $(EXC_DIR)/path_handler.c  $(EXC_DIR)/error_handler.c $(EXC_DIR)/heredoc.c  

# Source files and objects
SRC_OBJS = $(SRCS:.c=.o)
PAR_OBJS = $(PAR_SRC:.c=.o)
TOOL_OBJS = $(TOOL_SRC:.c=.o)
BUILD_OBJS = $(BUILD_SRC:.c=.o)
EXC_OBJS = $(EXC_SRC:.c=.o)

# ANSI color codes
GREEN = \033[0;32m
RED = \033[0;30m
NC = \033[0m

# Target: Build the library and, optionally, the executable
all: $(LIBFT) $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)%.c
	@echo "$(GREEN)Compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(PAR_DIR)/%.o: $(PAR_DIR)/%.c
	@echo "$(GREEN)Compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(TOOL_DIR)/%.o: $(TOOL_DIR)/%.c
	@echo "$(GREEN)Compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	@echo "$(GREEN)Compiling $<$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(NAME): $(SRC_OBJS) $(PAR_OBJS) $(TOOL_OBJS) $(BUILD_OBJS) ${EXC_OBJS}
	@echo "$(GREEN)Archiving object files$(NC)"
	$(CC) $(CFLAGS) $(SRC_OBJS) $(PAR_OBJS) $(TOOL_OBJS) $(BUILD_OBJS) ${EXC_OBJS} $(LIBFT) -lreadline -o $(NAME)

# Clean up
clean:
	@echo "$(RED)Cleaning up$(NC)"
	rm -f $(SRC_OBJS) $(PAR_OBJS) $(TOOL_OBJS) $(BUILD_OBJS) ${EXC_OBJS}
	make clean -C $(LIBFT_DIR)
# Force clean, including the library and executable
fclean: clean
	@echo "$(RED)Force cleaning$(NC)"
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
# Rebuild
re: fclean all
	@echo "$(GREEN)Rebuild complete$(NC)"

.PHONY: all clean fclean re
