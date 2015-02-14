#include "level.h"
#include <iostream>

#include <chrono>
#include <random>


//Load the level
bool Level::load(SDL_Renderer* pRenderer)
{
	//Initialize the background image	
	bg_image = IMG_Load(lvl_bg_path.c_str());
	
	//Initialize the ground image
	lvl_image = IMG_Load(lvl_ground_path.c_str());

	//Initialize the bg sprite
	bg_rect.w = 1024;
	bg_rect.h = 768;
	bg_rect.x = 0;
	bg_rect.y = 0;

	//Initialize the ground sprite
	sprite_rect.w = 64;
	sprite_rect.h = 64;
	sprite_rect.x = 0;
	sprite_rect.y = 0;

	//Load the map
	if(!load_map(lvl_map_path))
	{
		return false;
	}

	//Load level textures
	if(!init_textures(pRenderer)) 
	{
		return false;
	}

	//Initialize the sound
	lvl_music = Mix_LoadMUS(lvl_music_path.c_str());
	if(!lvl_music)
	{
		return false;
	}

	is_load = true;

	//Play background music
	play_bg_music();

	return true;
}


//Add rect to lvl_ground vector
void Level::add_rect(int pX, int pY)
{
	SDL_Rect tmp_rect;
	tmp_rect.w = 64;
	tmp_rect.h = 64;
	tmp_rect.x = pX * 64;
	tmp_rect.y = pY * 64;

	lvl_ground.push_back(tmp_rect);	
}

//Load the level map
bool Level::load_map(string pMapFilepath)
{
	ifstream lvl_file(pMapFilepath);
	if(lvl_file.is_open())
	{
		string line;
		int monster_x1{0};
		int monster_x2{0};
		float line_idx{0};
		float col_idx{0};

		while(getline(lvl_file, line))
		{
			for(auto lChar : line)
			{
				switch(lChar)
				{
					case '*':
						add_rect(col_idx, line_idx);
						break;
					case 'P':
						lvl_player = Player(lvl_player_path, col_idx, line_idx);
						break;
					case 'L':
						create_heart(col_idx, line_idx);			
						break;
					case '[':
						monster_x1 = col_idx;
						break;
					case ']':
						monster_x2 = col_idx;
						break;
					case 'D':
						lvl_door = Door(lvl_door_path, col_idx, line_idx);
						break;
				}
				col_idx++;
			}
			
			if(monster_x1 != monster_x2)
			{
				create_monster(monster_x1, monster_x2, line_idx);
			}

			monster_x1 = 0;
			monster_x2 = 0;
			col_idx = 0;
			line_idx++;
		}
		lvl_file.close();
	}
	else
	{
		return false;
	}
	return true;
}

//Generate new monster
void Level::create_monster(int pXmin, int pXmax, int pY)
{
	lvl_monsters.push_back(Monster(pXmin, pXmax, pY));
}

void Level::create_heart(int pX, int pY)
{
	Heart tmp_heart = Heart(pX, pY);
	if(lvl_hearts.size() == 0)
	{
		tmp_heart.set_visibility(true);
	}
	lvl_hearts.push_back(tmp_heart);
}

//Move monsters :D
void Level::move_monsters()
{
	for(auto& lMonster : lvl_monsters)
	{
		lMonster.move();
	}
}

//Initialize the texture to be rendered
bool Level::init_textures(SDL_Renderer* pRenderer)
{
	bg_texture = SDL_CreateTextureFromSurface(pRenderer, bg_image);
	if(bg_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(bg_image);
	
	lvl_texture = SDL_CreateTextureFromSurface(pRenderer, lvl_image);
	if(lvl_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(lvl_image);

	return true;
}

//Launch the music
void Level::play_bg_music()
{
	if(Mix_PlayMusic(lvl_music, -1) == -1)
	{
		std::cout << "Marche po !! " << Mix_GetError() << std::endl; 
	}
}

//Check for collision with a given SDL_Rect
bool Level::check_ground_collision(SDL_Rect* pPlayer)
{
	for(auto lGroundRect : lvl_ground)
	{
		if(SDL_HasIntersection(pPlayer, &lGroundRect))
		{
			return true;			
		}
	}
	return false;
}

//Check for collision between player_rect and the monsters
bool Level::check_monster_collision(SDL_Rect* pPlayer)
{
	for(auto lMonster : lvl_monsters)
	{
		if(SDL_HasIntersection(pPlayer, lMonster.get_rect()))
		{
			return true;			
		}
	}
	return false;
}

//Check for collisions between player_rect and the heart
bool Level::check_heart_collision()
{
	for(auto& lHeart : lvl_hearts)
	{
		if(lHeart.get_visibility())
		{
			SDL_Rect* lRect = lHeart.get_rect();
			if(SDL_HasIntersection(lvl_player.get_rect(), lRect))
			{
				lHeart.set_visibility(false);
				lHeart.eat();
				return true;
			}
		}
	}
	return false;
}

bool Level::check_door_collision()
{
	if(lvl_door.is_opened())
	{
		SDL_Rect* lRect = lvl_door.get_rect();
		if(SDL_HasIntersection(lvl_player.get_rect(), lRect))
		{
			return true;
		}
	}
	return false;
}

//Render the texture through given renderer
void Level::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, bg_texture, &bg_rect, &bg_rect);

	for(auto lGroundRect : lvl_ground)
	{	
		SDL_RenderCopy(pRenderer, lvl_texture, &sprite_rect, &lGroundRect);
	}

	for(auto lMonster : lvl_monsters)
	{
		lMonster.render(pRenderer); 
	}

	for(auto lHeart : lvl_hearts)
	{
		lHeart.render(pRenderer);
	}

	lvl_door.render(pRenderer);
}

int Level::get_remaining_hearts()
{
	int remain{0};
	for(auto lHeart : lvl_hearts)
	{
		if(!lHeart.is_eat())
		{
			remain++;
		}
	}
	return remain;
}

void Level::open_door()
{
	lvl_door.open();	
}

int Level::get_random(int pMin, int pMax)
{
	unsigned lSeed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine gen(lSeed);
	uniform_int_distribution<int> dist(pMin, pMax);

	return dist(gen);
}

void Level::set_random_heart_visible()
{
	int max = lvl_hearts.size()-1;

	int rand_val = get_random(0, max);
	while(lvl_hearts[rand_val].get_visibility())
	{
		rand_val = get_random(0, max);
	}
	lvl_hearts[rand_val].set_visibility(true);
}

//void Level::dispose()
//{
//	
//}
