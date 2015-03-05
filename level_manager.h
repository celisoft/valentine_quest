#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "level.h"
#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class LevelManager
{
	private:
		const string INDEX_FILENAME = "lvl_index";
		const string LEVEL_DESC_FILENAME = "lvl_desc";
		const string LEVEL_MAP_FILENAME = "lvl_map";

		string level_base_path;
		string level_data_path;
		string level_asset_path;

		string index_path;

		vector<Level> levels;
		int current_level = 0;

		//initialize paths
		void init_paths();
	public:
		//Constructor
		LevelManager()
		{
			init_paths();
		}

		//Load the lvl_index file
		bool load_index();

		//Load level and add it to levels vector
		bool load_level(string pLevelDescPath);

		//Return the next level
		bool prepare_next_level(SDL_Renderer* pRenderer);

		//Return the current level
		Level* get_current_level(SDL_Renderer* pRenderer);
};

#endif
