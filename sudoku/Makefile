CC = gcc
CFLAGS = -Wall -Wextra -O3
SOURCES = sudoku_backtracking.c sudoku_solver.c main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = solver

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
