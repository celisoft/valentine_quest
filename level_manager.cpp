#include "level_manager.h"
#include <fstream>
#include <iostream>

//Init paths
void LevelManager::init_paths()
{
	char* path = SDL_GetBasePath();
	if(path == nullptr)
	{
		level_base_path = SDL_strdup("./");
		level_data_path = SDL_strdup("./data/");
		level_asset_path = SDL_strdup("./assets/");	
	}
	else
	{
		level_base_path = SDL_strdup(path);
		level_data_path = level_base_path + "data/";
		level_asset_path = level_base_path + "assets/";
		index_path = level_data_path + INDEX_FILENAME;
		SDL_free(path);
	}
}

//Load the lvl_index file
bool LevelManager::load_index()
{
	ifstream index_file(index_path);
	if(index_file.is_open())
	{
		string line;
		while(getline(index_file, line))
		{
			load_level(line);
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
bool LevelManager::load_level(std::string pId)
{
	std::string lvl_desc_path = level_data_path + pId + "/" + LEVEL_DESC_FILENAME;
	ifstream desc_file(lvl_desc_path);
	if(desc_file.is_open())
	{
		std::string lvl_bg, lvl_ground, lvl_music, lvl_map, lvl_player, lvl_door;

		getline(desc_file, lvl_bg);
		getline(desc_file, lvl_ground);
		getline(desc_file, lvl_music);
		getline(desc_file, lvl_player);
		getline(desc_file, lvl_door);
		
		lvl_bg = level_asset_path + lvl_bg;
		lvl_ground = level_asset_path + lvl_ground;
		lvl_music = level_asset_path + lvl_music; 
		lvl_player = level_asset_path + lvl_player;
		lvl_door = level_asset_path + lvl_door;
		lvl_map = level_data_path + pId + "/" + LEVEL_MAP_FILENAME;

		desc_file.close();
		levels.push_back(Level(lvl_bg, lvl_ground, lvl_music, lvl_map, lvl_player, lvl_door));
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
			current_level = lvl_ind;
			levels[lvl_ind-1].unload();

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

