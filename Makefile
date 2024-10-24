CC=gcc
INSTALLDIR=/opt/asteroids
DESKTOPDIR=/usr/share/applications
LDFLAGS=-lallegro -lallegro_font -lallegro_primitives -lallegro_image
OBJECTS=$(SOURCES:.c=.o)
SRCDIR=src
BINDIR=bin
TARGET=$(BINDIR)/Asteroids
ASSETS=assets
SOURCES=$(wildcard $(SRCDIR)/*.c)

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BINDIR):
	mkdir -p $(BINDIR)
	cp -r $(ASSETS) $(BINDIR)

install: $(TARGET)
	mkdir -p $(INSTALLDIR)
	cp -r $(ASSETS) $(INSTALLDIR)

	install -D $(TARGET) $(INSTALLDIR)
	install -D Asteroids.desktop $(DESKTOPDIR)/Asteroids.desktop
	chmod +x $(DESKTOPDIR)/Asteroids.desktop

uninstall:
	rm -rf $(INSTALLDIR)
	rm -f $(DESKTOPDIR)/Asteroids.desktop

clean:
	rm -rf $(BINDIR)
	rm -rf src/*.o

.PHONY: all install uninstall clean
