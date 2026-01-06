CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = fsexplorer
SOURCES = main.c fileops.c syscalls.c directories.c processes.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

debug: CFLAGS += -DDEBUG -fsanitize=address
debug: $(TARGET)

format:
	clang-format -i *c *.h

.PHONY: clean debug format