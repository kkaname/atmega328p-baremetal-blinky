CC = avr-gcc
CFLAGS = -mmcu=atmega328p -DF_CPU=16000000UL -Os -Wall -Wextra -Werror

TARGET = blinky.elf
SRC = src/blinky.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET)
