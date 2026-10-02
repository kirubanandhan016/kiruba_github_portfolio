CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -O2
TARGET=addressbook
SRC=src/main.c src/address_book.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -Iinclude $(SRC) -o $@

clean:
	rm -f $(TARGET) contacts.txt
