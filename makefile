CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = fsexplorer
SOURCES = main.c fileops.c syscalls.c directories.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

debug: CFLAGS += -DDEBUG -fsanitize=address
debug: $(TARGET)

.PHONY: clean debug