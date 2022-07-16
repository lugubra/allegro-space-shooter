CC=gcc
LDFLAGS=-lallegro -lallegro_font -lallegro_primitives -lallegro_image
SOURCES= \
	src/main.c src/game.c src/asteroids.c src/ship.c src/gun.c src/bullets.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=asteroids

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@