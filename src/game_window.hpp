#ifndef GAME_WINDOW_HPP_
#define GAME_WINDOW_HPP_

#include "level_manager.hpp"
#include "menu.hpp"

#include <SDL2/SDL.h>

#include <string>

class GameWindow {
	private:
		bool is_running;
		bool is_playing = false;

		SDL_Window* display;
		SDL_Renderer* renderer;

		std::string base_path;
		Menu menu;
		LevelManager lvl_manager;

	public:
		// Constructor
		GameWindow() {
			display = nullptr;
			renderer = nullptr;
		}

		// Initialize the game display
		bool init();

		// Display the game
		bool run();

		// Catch game events
		void on_event(SDL_Event* event);
};

#endif  // GAME_WINDOW_HPP_
