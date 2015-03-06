#Define vars
CC = g++
FLAGS = -Wall -std=c++11
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer 
EXEC = valentine_quest
OBJ_FILES = main.o game_window.o menu.o level_manager.o level.o player.o monster.o heart.o door.o position.o
INSTALL_DIR = /opt/valentine_quest
LAUNCHER = scripts/valentine_quest
LAUNCHER_DIR = /usr/local/bin
README = readme.md

#Define the ALL scope (default)
all: clean game 

#Create the executable file
game : main
	$(CC) -o $(EXEC) $(LIBS) $(OBJ_FILES) 

main: complex_components
	$(CC) -c $(FLAGS) main.cpp

complex_components: basic_components
	$(CC) -c $(FLAGS) game_window.cpp level_manager.cpp level.cpp

basic_components: 
	$(CC) -c $(FLAGS) menu.cpp player.cpp monster.cpp heart.cpp door.cpp position.cpp

clean: 
	rm -f *.o $(EXEC)

install:
	mkdir -p $(INSTALL_DIR)
	cp -R assets/ $(INSTALL_DIR)
	cp -R data/ $(INSTALL_DIR)
	cp $(EXEC) $(INSTALL_DIR)
	cp $(README) $(INSTALL_DIR)
	cp $(LAUNCHER) $(LAUNCHER_DIR)
	chmod a+x $(LAUNCHER_DIR)/$(EXEC)
	chmod -R a+rx $(INSTALL_DIR)

uninstall:
	rm -R $(INSTALL_DIR)
	rm $(LAUNCHER_DIR)/$(EXEC)
