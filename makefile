CC = avr-gcc
MCU = atmega645
PROG = usbtiny
TARGET = firmware

ARCH = AVR8
F_CPU = 8000000
F_USB = $(F_CPU)
BOARD = USER

LFUSE = 0xFF
HFUSE = 0x99
EFUSE = 0xFF

INCLUDE_DIR = include
BUILD_DIR = build
SOURCE_DIR = src

SRCS = $(wildcard $(SOURCE_DIR)/*.c) $(wildcard $(INCLUDE_DIR)/*.c)
HEADS = $(wildcard $(SOURCE_DIR)/*.h ) $(wildcard $(INCLUDE_DIR)/*.h )
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(patsubst %.c,%.o, $(SRCS) )))

_INCLUDES = 
INCLUDES = $(addprefix -I$(INCLUDE_DIR)/, $(_INCLUDES)) -I/usr/avr/include/ -Iinclude/
_DEFS = F_CPU=$(F_CPU)
DEFS = $(addprefix -D,$(_DEFS))

CFLAGS = -g $(INCLUDES) -Wall -mmcu=$(MCU) $(DEFS) -ffunction-sections -Os
LDFLAGS = -Wl,--gc-sections

all: $(BUILD_DIR)/$(TARGET).elf $(TARGET).hex

burn: $(TARGET).hex
	avrdude -p $(MCU) -c $(PROG) -U flash:w:$(TARGET).hex:i

fuses:
	avrdude -p $(MCU) -c $(PROG) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m

clean:
	rm -f *.hex build/*

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	avr-gcc $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.hex: $(BUILD_DIR)/%.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADS)
	avr-gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/%.c $(HEADS)
	avr-gcc $(CFLAGS) -c $< -o $@
