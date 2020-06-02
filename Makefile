#Define vars
CXX = g++
FLAGS = -Wall -std=c++11
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer 
EXEC = valentine_quest

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

INSTALL_DIR = /opt/valentine_quest
LAUNCHER = scripts/valentine_quest
LAUNCHER_DIR = /usr/local/bin
README = readme.md

#Create the executable file
valentine_quest: $(OBJ)
	$(CXX) $(FLAGS) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean: 
	rm -f $(OBJ) valentine_quest

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
