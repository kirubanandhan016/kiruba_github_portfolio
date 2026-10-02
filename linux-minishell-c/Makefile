CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -O2
TARGET=minishell
SRC=src/main.c src/parser.c src/builtins.c src/executor.c src/signals.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -Iinclude $(SRC) -o $@

clean:
	rm -f $(TARGET)
