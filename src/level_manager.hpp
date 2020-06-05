#ifndef LEVEL_MANAGER_HPP_
#define LEVEL_MANAGER_HPP_

#include "level.hpp"

#include <string>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

class LevelManager {
	private:
		const std::string INDEX_FILENAME = "lvl_index";
		const std::string LEVEL_DESC_FILENAME = "lvl_desc";
		const std::string LEVEL_MAP_FILENAME = "lvl_map";

		std::string level_base_path;
		std::string level_data_path;
		std::string level_asset_path;
		std::string index_path;

		std::vector<Level> levels;
		int current_level = 0;

		// Initialize paths
		void init_paths(std::string pPath);

		// Return the next level
		bool prepare_next_level(SDL_Renderer* pRenderer);

	public:
		// Constructor
		LevelManager() {}

		// Load the lvl_index file
		bool load_index(SDL_Renderer* pRenderer, std::string pPath);

		// Load level and add it to levels vector
		bool load_level(std::string pLevelDescPath);

		// Display the current level
		bool display(SDL_Renderer* pRenderer);

		// Reset progression
		void reset_progress();

		// Event dispatcher
		void on_event(SDL_Event* pEvent);
};

#endif  // LEVEL_MANAGER_HPP_

