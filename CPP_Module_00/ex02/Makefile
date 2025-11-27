NAME = megaphone

# Source files organized by directories
MAIN_C = main.c

THREADS_C = threads.c

ROUTINES_C = philosopher_routine.c routine_helpers.c fork_management.c routine_utils.c

PHILOSOPHER_C = philosopher_init.c philosopher_free.c philosopher_struct.c

TABLE_C = table_struct_handler.c

UTILS_C = input_utils.c memory_utils.c philosopher_checks.c print_utils.c general_utils.c

# Header files
HEADER_LIST = philo.h
HEADER_DIRECTORY = srcs/
HEADERS = $(addprefix $(HEADER_DIRECTORY), $(HEADER_LIST))

# Source directories
SRCS_DIRECTORY = srcs/
ROUTINES_DIRECTORY = srcs/routines/
PHILOSOPHER_DIRECTORY = srcs/philosopher/
TABLE_DIRECTORY = srcs/table/
UTILS_DIRECTORY = srcs/utils/

# Source files with full paths
MAIN_LIST = $(MAIN_C)
MAIN = $(addprefix $(SRCS_DIRECTORY), $(MAIN_LIST))

THREADS_LIST = $(THREADS_C)
THREADS = $(addprefix $(SRCS_DIRECTORY), $(THREADS_LIST))

ROUTINES_LIST = $(ROUTINES_C)
ROUTINES = $(addprefix $(ROUTINES_DIRECTORY), $(ROUTINES_LIST))

PHILOSOPHER_LIST = $(PHILOSOPHER_C)
PHILOSOPHER = $(addprefix $(PHILOSOPHER_DIRECTORY), $(PHILOSOPHER_LIST))

TABLE_LIST = $(TABLE_C)
TABLE = $(addprefix $(TABLE_DIRECTORY), $(TABLE_LIST))

UTILS_LIST = $(UTILS_C)
UTILS = $(addprefix $(UTILS_DIRECTORY), $(UTILS_LIST))

# All source files
SRCS_LIST = $(MAIN) $(THREADS) $(ROUTINES) $(PHILOSOPHER) $(TABLE) $(UTILS)

# Object files
OBJECT_LIST = $(notdir $(SRCS_LIST:.c=.o))
OBJECTS_DIRECTORY = objects/
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECT_LIST))

# Compiler settings
CC = c++
CFLAGS = -g -Wall -Werror -Wextra -std=c++98
INCLUDES = -I$(SRCS_DIRECTORY)

# Colors
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m

# Main target
$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling files..."
	@if $(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) -o $(NAME); then \
		echo "[" "$(GREEN)OK$(RESET)" "] | Compilation successful!"; \
		make norm -s; \
		echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) created successfully!"; \
	else \
		echo "[" "$(RED)Error$(RESET)" "] | An error occurred while creating $(NAME)."; \
		make clean > /dev/null 2>&1; \
		echo "[" "$(RED)Error$(RESET)" "] | All objects cleaned."; \
	fi

# Create objects directory structure
$(OBJECTS_DIRECTORY):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Creating objects directory structure..."
	@mkdir -p $(OBJECTS_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(ROUTINES_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(PHILOSOPHER_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(TABLE_DIRECTORY)
	@mkdir -p $(OBJECTS_DIRECTORY)$(UTILS_DIRECTORY)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Objects directory structure ready!"

# Compile object files
$(OBJECTS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(ROUTINES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(PHILOSOPHER_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(TABLE_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o : $(UTILS_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

all: $(NAME)

# Clean targets
clean:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing object files..."
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Object files removed."

fclean: clean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing $(NAME)..."
	@rm -rf $(NAME)
	@rm -rf .norminette.log
	@echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) removed."

# Norminette check
norm:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Running norminette..."
	@if norminette $(SRCS_DIRECTORY) > .norminette.log 2>&1; then \
		if grep -q "Error!" .norminette.log; then \
			echo "[" "$(RED)!!$(RESET)" "] | Norminette found errors:"; \
			grep "Error!" .norminette.log | awk '{print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
		else \
			echo "[" "$(GREEN)OK$(RESET)" "] | Norminette passed!"; \
		fi; \
	else \
		echo "[" "$(RED)XX$(RESET)" "] | Norminette Error!"; \
		norminette $(SRCS_DIRECTORY) 2>&1 | awk '/Error!/ {print "[ " "$(RED)!!$(RESET)" " ] | " $$0}'; \
	fi

# Rebuild target
re: fclean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Rebuilding $(NAME)..."
	@make -s

# Help target
help:
	@echo "Available targets:"
	@echo "  $(NAME)     - Build the $(NAME) executable"
	@echo "  clean       - Remove object files"
	@echo "  fclean      - Remove object files and executable"
	@echo "  re          - Rebuild everything"
	@echo "  norm        - Run norminette check"
	@echo "  help        - Show this help message"

.PHONY: all clean fclean re norm help