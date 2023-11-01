# Makefile
CC = gcc
CFLAGS = -Isrc -Wall -Wextra -Werror -O3 -std=c99 -march=native `pkg-config --cflags sdl2 SDL2_image`
LDLIBS = `pkg-config --libs sdl2 SDL2_image`

FILES = $(shell find . -name '*.c')

NAME = main

all: $(NAME)

show:
	@echo $(FILES)

main:	$(FILES) 
	$(CC) $< $(CFLAGS) -o $@
	@echo project built successfully
clean:
	rm -rf main
	@echo "cleaning done"
