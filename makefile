CC = clang
CFLAGS = -std=c11 -Wall -Wextra -I src/days
SRCS = src/main.c $(wildcard src/days/*.c)
TARGET = bin/a.out

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

run: $(TARGET)
	./$(TARGET) $(day)

clean:
	rm -f $(TARGET)

debug:
	@echo "Files found: $(SRCS)"
