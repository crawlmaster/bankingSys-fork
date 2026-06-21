CC = gcc -std=c17
CFLAGS = -Wall -Werror -Wextra -g

TARGET = test_limits testHashingFunction

all : $(TARGET)

test_limits : test_limits.c
	$(CC) $(CFLAGS) -o test_limits test_limits.c 

testHashingFunction : testHashingFunction.c
	$(CC) $(CFLAGS) -o testHashingFunction testHashingFunction.c

clean :
	-rm -rf *.o $(TARGET)
