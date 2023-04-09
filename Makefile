# Compiler and linker options
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Iexternal
LDFLAGS = -lSDL2 -lSDL2_gfx

# Source and object files
SRC = src/main.c src/simulation.c src/graphics.c
OBJ = $(SRC:src/%.c=obj/%.o)

# Target executable
TARGET = bin/simulation

ifeq ($(shell uname),Darwin)
	LDFLAGS += -L/opt/homebrew/lib
else
	LDFLAGS += -L/usr/local/lib
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

build: clean all
