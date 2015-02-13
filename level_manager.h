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
		const string LEVEL_BASE_PATH = "data";
		const string INDEX_FILEPATH = LEVEL_BASE_PATH + "/lvl_index";
		const string LEVEL_DESC_FILENAME = "lvl_desc";

		vector<Level> levels;
		int current_level = 0;

	public:
		//Constructor
		LevelManager()
		{
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
