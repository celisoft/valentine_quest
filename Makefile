#Define vars
CC = clang++
FLAGS = -Wall -std=c++11
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer
EXEC = valentine_quest

#Define the ALL scope (default)
all: clean game 

#Create the executable file
game : main
	$(CC) -o $(EXEC) $(LIBS) main.o game_window.o level.o player.o monster.o position.o

main: game_window
	$(CC) -c $(FLAGS) main.cpp

game_window: game_components
	$(CC) -c $(FLAGS) game_window.cpp

game_components: position.o
	$(CC) -c $(FLAGS) player.cpp monster.cpp level.cpp

position.o:
	$(CC) -c $(FLAGS) position.cpp

clean: 
	rm -f *.o $(EXEC)
