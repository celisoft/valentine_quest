#include "level_manager.h"
#include <fstream>

//Init paths
void LevelManager::init_paths(string pPath)
{
	level_base_path = pPath;
	level_data_path = level_base_path + "data/";
	level_asset_path = level_base_path + "assets/";
	index_path = level_data_path + INDEX_FILENAME;
}

//Load the lvl_index file
bool LevelManager::load_index(SDL_Renderer* pRenderer, string pPath)
{
	init_paths(pPath);
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

	if(!levels[current_level].load(pRenderer))
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
		levels.push_back(Level(lvl_bg, lvl_ground, lvl_music, lvl_map, lvl_player, lvl_door, level_asset_path));
	}
	else
	{
		return false;
	}
	return true;
}

//Display the current level
bool LevelManager::display(SDL_Renderer* pRenderer)
{
	if(!levels[current_level].is_loaded())
	{
		levels[current_level].load(pRenderer);
	}
	else
	{
		if(levels[current_level].is_finished())
		{
			if(!prepare_next_level(pRenderer))
			{
				return false;
			}
		}
	}

	if(!levels[current_level].render(pRenderer))
	{
		reset_progress();
		return false;
	}

	return true;
}

//Reset played levels
void LevelManager::reset_progress()
{
	for(int l=0; l<=current_level; l++)
	{
		levels[l].unfinish();
		levels[l].unload();
	}

	current_level = 0;
}

//Start the next level and return it
bool LevelManager::prepare_next_level(SDL_Renderer* pRenderer)
{
	int lvl_ind{0};
	for(auto &lvl : levels)
	{
		if(!lvl.is_finished())
		{
			if(!lvl.load(pRenderer))
			{
				return false;
			}
			current_level = lvl_ind;

			return true;
		}
		lvl_ind++;
	}
	return false;
}

//Event dispatcher
void LevelManager::on_event(SDL_Event* pEvent)
{
	levels[current_level].on_event(pEvent);
}
