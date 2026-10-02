CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic -O2
TARGET=steg
SRC=src/main.c src/bmp.c src/steg.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -Iinclude $(SRC) -o $@

clean:
	rm -f $(TARGET) *.o
