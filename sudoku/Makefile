#Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3
LDFLAGS =
LDLIBS =


SRC = sudoku_backtracking.c sudoku_solver.c main.c 
OBJ = ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main
# END
