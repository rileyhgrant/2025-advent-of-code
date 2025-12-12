CC = clang
CFLAGS = -std=c11 -Wall -Wextra -I src/days -I src/utils
SRCS = src/main.c $(wildcard src/days/*.c) $(wildcard src/utils/*.c)
TARGET = bin/a.out

.PHONY: all clean run debug format

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

asan: CFLAGS += -fsanitize=address -g -fno-omit-frame-pointer
asan: clean $(TARGET)

run: format $(TARGET)
	./$(TARGET) $(day)

clean:
	rm -f $(TARGET)

debug:
	@echo "Files found: $(SRCS)"

format:
	@echo "Formatting source files..."
	find src -name "*.c" -o -name "*.h" | xargs clang-format -i
