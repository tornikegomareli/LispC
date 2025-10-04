CC = gcc
CFLAGS = -Wall -Wextra -g -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lreadline
TARGET = hello

all: $(TARGET)

$(TARGET): main.c mpc.c
	$(CC) $(CFLAGS) main.c mpc.c -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean