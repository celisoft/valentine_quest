#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL2/SDL.h>
#include "level.h"
#include "level_manager.h"
#include "player.h"
#include <iostream>

class GameWindow
{
	private:
 		bool is_running;   
		SDL_Window* display;
		SDL_Renderer* renderer;

		Level* current_lvl;
		Player* player;
		LevelManager lvl_manager;

	public:
		//Constructor
		GameWindow()
		{
			display = nullptr;
			renderer = nullptr;

			if(!lvl_manager.load_index())
			{
				std::cout << "Bad file !!" << std::endl;
			}
		}

		//Initialize the game display
		bool init();

		//Display the game
		bool run();

		//Catch game events
		void on_event(SDL_Event* event);

		//Imitate gravity for player
		void player_fall_down();
};

#endif
