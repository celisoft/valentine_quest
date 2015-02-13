#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL2/SDL.h>
#include "level.h"
#include "player.h"

class GameWindow
{
	private:
 		bool is_running;   
		SDL_Window* display;
		SDL_Renderer* renderer;

		Player player;
		Level lvl = Level("test.lvlmap", "assets/grounds/ground_nuaga.png");

	public:
		//Constructor
		GameWindow()
		{
			display = nullptr;
			renderer = nullptr;

			player.set_pos(lvl.get_player_start_position());
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
