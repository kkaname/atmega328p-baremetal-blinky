CC = avr-gcc
CFLAGS = -mmcu=atmega328p -DF_CPU=16000000UL -Os -Wall -Wextra -Werror

SRC = src/blinky.c
TARGET = blinky.hex
ELF = blinky.elf
OBJ = blinky.o

all: $(TARGET)

$(TARGET): $(ELF)
	avr-objcopy -O ihex -R .eeprom $< $@

$(ELF): $(OBJ)
	$(CC) $(CFLAGS) -Wl,-T,linker.ld -o $@ $(OBJ)

$(OBJ): $(SRC) 
	$(CC) $(CFLAGS) -Os -c $^ -o $@


flash: $(TARGET)
	avrdude -c usbasp -p m328p -U flash:w:blinky.hex:i

.PHONY: clean flash

clean:
	rm -f $(TARGET) $(ELF) $(OBJ)
