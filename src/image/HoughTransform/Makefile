CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image`

all:hough

SRC = hough.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

hough: hough.o


.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END
