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

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g 
SRC = coreFile.c 
EXT = ./src/cryptString.c ./src/configDB.c ./src/clientConfig.c ./src/hashTable.c

EXEC_PATH=executableFiles
EXEC=$(EXEC_PATH)/coreFile

all : $(EXEC)

$(EXEC): $(SRC)
	@echo ""
	@echo "$(newline)$(BOLD_BLUE)[INFO]$(NC) $(BLUE) - Se creeaza directorul pentru executabil : $(EXEC_PATH)$(NC)"
	@mkdir -p $(EXEC_PATH)
	@echo "$(BOLD_YELLOW)[Compiling]$(NC)$(YELLOW) - Se compileaza executabilul : $(SRC)$(NC)"
	@$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(EXT)
	@echo "$(BOLD_GREEN)[Success]$(NC)$(GREEN) - Executabilul a fost creat cu succes in : $(EXEC)$(NC)"
	@echo "$(BOLD_BLUE)[INFO]$(NC)$(BLUE) - run executable file with : make run$(NC)$(newline)"
	@echo ""

run: $(EXEC)
	@echo ""
	@echo "$(newline)$(BOLD_BLUE)[running program ...]$(NC)$(newline)"
	@echo ""

	@./$(EXEC)

valgrind: $(EXEC)
	@echo ""
	@echo "$(BOLD_BLUE)[Valgrind]$(NC)$(BLUE) - Checking for memory leaks...$(NC)"
	@echo ""

	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)

clean :
	@echo ""
	@echo "$(newline)$(BOLD_YELLOW)[cleaning ...]$(NC)$(YELLOW) Removing executabile files and temporary used directories$(newline)"
	@echo ""

	@-rm -rf $(EXEC_PATH)
