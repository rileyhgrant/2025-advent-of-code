CC = clang
CFLAGS = -std=c11 -Wall -Wextra -I src/days
SRCS = src/main.c $(wildcard src/days/*.c)
TARGET = bin/a.out

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

asan: CFLAGS += -fsanitize=address -g -fno-omit-frame-pointer
asan: clean $(TARGET)

run: $(TARGET)
	./$(TARGET) $(day)

clean:
	rm -f $(TARGET)

debug:
	@echo "Files found: $(SRCS)"
