#include "level_manager.h"
#include <fstream>
#include <iostream>

//Load the lvl_index file
bool LevelManager::load_index()
{
	ifstream index_file(INDEX_FILEPATH);
	if(index_file.is_open())
	{
		string line;
		while(getline(index_file, line))
		{
			load_level(LEVEL_BASE_PATH + "/" + line + "/" + LEVEL_DESC_FILENAME);
		}	
		index_file.close();	
	}
	else
	{
		return false;
	}
	return true;	
}

//Load the level description file and creates a Level
bool LevelManager::load_level(std::string pLevelDescPath)
{
	ifstream desc_file(pLevelDescPath);
	if(desc_file.is_open())
	{
		std::string lvl_bg, lvl_ground, lvl_music, lvl_map, lvl_player;

		getline(desc_file, lvl_bg);
		getline(desc_file, lvl_ground);
		getline(desc_file, lvl_music);
		getline(desc_file, lvl_map);
		getline(desc_file, lvl_player);

		desc_file.close();
		levels.push_back(Level(lvl_bg, lvl_ground, lvl_music, lvl_map, lvl_player));
	}
	else
	{
		return false;
	}
	return true;
}

//Start the next level and return it
bool LevelManager::prepare_next_level(SDL_Renderer* pRenderer)
{
	int lvl_ind{0};
	for(auto lvl : levels)
	{
		if(!lvl.is_finished())
		{
			if(!lvl.load(pRenderer))
			{
				return false;
			}
			
			//Play background music
			lvl.play_bg_music();

			current_level = lvl_ind;

			return true;
		}
		lvl_ind++;
	}
	return false;
}

Level* LevelManager::get_current_level(SDL_Renderer* pRenderer) 
{
	if(!levels[current_level].is_loaded())
	{
		levels[current_level].load(pRenderer);
	}
	return &levels[current_level];
}
