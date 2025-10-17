CC = clang
CFLAGS = -std=c11 -Wall -Wextra
SRC = src/day01.c
TARGET = bin/a.out

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)