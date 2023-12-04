CC = gcc
CFLAGS = -Wall -Wextra -O3 -I../epurator -I../separator `pkg-config --cflags sdl2 SDL2_image`
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm
SOURCES =  main.c ../epurator/epurator.c ../separator/separator.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = drill

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

