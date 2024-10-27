CC=gcc

APP_NAME=Asteroids
APP_DIR=$(APP_NAME).AppDir
INSTALL_DIR=/opt/asteroids
DESKTOP_DIR=/usr/share/applications
DESKTOP_FILE=$(APP_NAME).desktop

RELEASE_DIR=release
ASSETS=assets
LIB_DIR=lib
SRC_DIR=src
TARGET=$(RELEASE_DIR)/$(APP_NAME)
LDFLAGS=-Wall -Wextra -g -lallegro -lallegro_font -lallegro_primitives -lallegro_image

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(RELEASE_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(RELEASE_DIR):
	mkdir -p $(RELEASE_DIR)
	cp -r $(ASSETS)/ $(RELEASE_DIR)/

install: $(TARGET)
	mkdir -p $(INSTALL_DIR)
	cp -r $(ASSETS) $(INSTALL_DIR)

	install -D $(TARGET) $(INSTALL_DIR)
	install -D $(DESKTOP_FILE) $(DESKTOP_DIR)/$(DESKTOP_FILE)
	chmod +x $(DESKTOP_DIR)/$(DESKTOP_FILE)

uninstall:
	rm -rf $(INSTALL_DIR)
	rm -f $(DESKTOP_DIR)/$(DESKTOP_FILE)

clean:
	rm -rf $(RELEASE_DIR)
	rm -rf $(APP_DIR)
	rm -rf src/*.o

AppImage: $(TARGET)
	# 1. Set up the AppDir structure
	mkdir -p $(APP_DIR)/usr/bin
	mkdir -p $(APP_DIR)/usr/lib
	mkdir -p $(APP_DIR)/usr/share/applications

	# 2. Copy files
	cp -r $(RELEASE_DIR)/* $(APP_DIR)/usr/bin/
	cp -r $(LIB_DIR)/ $(APP_DIR)/usr/
	cp $(ASSETS)/$(APP_NAME).png $(APP_DIR)/
	cp package/AppRun-x86_64 $(APP_DIR)/AppRun

	# 3. Create the .desktop file
	echo "[Desktop Entry]\n\
	Version=1.1\n\
	Name=$(APP_NAME)\n\
	Exec=$(APP_NAME)\n\
	Icon=$(APP_NAME)\n\
	StartupWMClass=Asteroids\n\
	Terminal=false\n\
	Categories=Game;\n\
	Type=Application" > $(APP_DIR)/usr/share/applications/$(DESKTOP_FILE)

	chmod +x $(APP_DIR)/usr/share/applications/$(DESKTOP_FILE)

	ln -s usr/share/applications/$(DESKTOP_FILE) $(APP_DIR)/$(DESKTOP_FILE)

.PHONY: all install uninstall clean
