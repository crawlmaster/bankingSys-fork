define newline

endef

# COLORS
RED 		= \033[0;31m
GREEN 	= \033[0;32m
YELLOW 	= \033[0;33m
BLUE 		= \033[0;34m
NC 			= \033[0m

# BOLD colors and fonts

BOLD 			= \033[1m
BOLD_BLUE = \033[1;34m
BOLD_GREEN 	= \033[1;32m
BOLD_YELLOW 	= \033[1;33m

# make rules for compiling programs

CC = gcc -std=c99
CFLAGS = -Wall -Werror -Wextra -g 
SRC = coreFile.c 
EXT = ./src/cryptString.c ./src/configDB.c ./src/clientConfig.c ./src/hashTable.c

EXEC_PATH=executableFiles
EXEC=$(EXEC_PATH)/coreFile

all : $(EXEC)

$(EXEC): $(SRC)
	@printf ""
	@printf "$(newline)$(BOLD_BLUE)[INFO]$(NC) $(BLUE) - Se creeaza directorul pentru executabil : $(EXEC_PATH)$(NC)"
	@mkdir -p $(EXEC_PATH)
	@printf "$(BOLD_YELLOW)[Compiling]$(NC)$(YELLOW) - Se compileaza executabilul : $(SRC)$(NC)"
	@$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(EXT)
	@printf "$(BOLD_GREEN)[Success]$(NC)$(GREEN) - Executabilul a fost creat cu succes in : $(EXEC)$(NC)"
	@printf "$(BOLD_BLUE)[INFO]$(NC)$(BLUE) - run executable file with : make run$(NC)$(newline)"
	@printf ""

run: $(EXEC)
	@printf ""
	@printf "$(newline)$(BOLD_BLUE)[running program ...]$(NC)$(newline)"
	@printf ""

	@./$(EXEC)

valgrind: $(EXEC)
	@printf ""
	@printf "$(BOLD_BLUE)[Valgrind]$(NC)$(BLUE) - Checking for memory leaks...$(NC)"
	@printf ""
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)

clean :
	@printf ""
	@printf "$(newline)$(BOLD_YELLOW)[cleaning ...]$(NC)$(YELLOW) Removing executabile files and temporary used directories$(newline)"
	@printf ""

	@-rm -rf $(EXEC_PATH)

# Custom code formatting rule
format:
	clang-format -i -style=file *.c src/*.c include/*.h
