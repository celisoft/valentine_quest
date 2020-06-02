#include "level.hpp"
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

	//Initialize the music
	lvl_music = Mix_LoadMUS(lvl_music_path.c_str());
	if(!lvl_music)
	{
		return false;
	}

	//Initialize the beep sound
	lvl_beep = Mix_LoadWAV((lvl_asset_path + "sfx/beep.wav").c_str());
	if(lvl_beep == nullptr)
	{
		return false;
	}
	Mix_VolumeChunk(lvl_beep, 60);

	lvl_door_open = Mix_LoadWAV((lvl_asset_path + "sfx/door_open.ogg").c_str());
	if(lvl_door_open == nullptr)
	{
		return false;
	}
	Mix_VolumeChunk(lvl_door_open, 30);

	is_load = true;

	//Play background music
	play_bg_music();

	return true;
}

//Unload level
void Level::unload()
{
	//Destroy textures
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(lvl_texture);
	SDL_DestroyTexture(lvl_player.get_texture());
	SDL_DestroyTexture(lvl_door.get_texture());
	
	for(auto& lMonster : lvl_monsters)
	{
		lMonster.dispose();
	}
	for(auto& lHeart : lvl_hearts)
	{
		lHeart.dispose();	
	}

	//Stop music
	Mix_HaltMusic();
	Mix_FreeMusic(lvl_music);

	//Free sounds
	Mix_FreeChunk(lvl_beep);
	Mix_FreeChunk(lvl_door_open);

	lvl_ground.clear();
	lvl_monsters.clear();
	lvl_hearts.clear();
	lvl_player.reborn();

	is_load = false;
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
	lvl_monsters.push_back(Monster(lvl_asset_path, pXmin, pXmax, pY));
}

void Level::create_heart(int pX, int pY)
{
	Heart tmp_heart = Heart(lvl_asset_path, pX, pY);
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

//Initialize textures to be rendered
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

	for(auto& lMonster : lvl_monsters)
	{
		if(!lMonster.init_texture(pRenderer))
		{
			return false;
		}
	}

	for(auto& lHeart : lvl_hearts)
	{
		if(!lHeart.init_texture(pRenderer))
		{
			return false;
		}
	}

	if(!lvl_door.init_texture(pRenderer))
	{
		return false;
	}

	if(!lvl_player.init_texture(pRenderer))
	{
		return false;
	}

	return true;
}

//Launch the music
void Level::play_bg_music()
{
	Mix_PlayMusic(lvl_music, -1);
	Mix_VolumeMusic(30);
}

//Check for collision with a given SDL_Rect
bool Level::check_ground_collision()
{
	for(auto lGroundRect : lvl_ground)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), &lGroundRect))
		{
			return true;			
		}
	}
	return false;
}

//Check for collision between player_rect and the monsters
bool Level::check_monster_collision()
{
	for(auto lMonster : lvl_monsters)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), lMonster.get_rect()))
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
				//Play the beep !
				Mix_PlayChannel(-1, lvl_beep, 0);
				
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
bool Level::render(SDL_Renderer* pRenderer)
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

	current_time = SDL_GetTicks();
	if(current_time > next_fall_down)
	{
		if(lvl_player.is_jumping())
		{
			lvl_player.walk();
		}
		else
		{
			lvl_player.fall(lvl_ground);
		}
		next_fall_down = current_time + 80;
	}

	//Check if the player get the visible heart
	if(check_heart_collision())
	{
		if(get_remaining_hearts() == 0)
		{
			open_door();
		}
		else
		{
			set_random_heart_visible();
		}
	}

	//Check if the player is in front of the door
	if(check_door_collision())
	{
		is_finish = true;
	}

	//End the game if the player is killed	
	if(check_monster_collision() == true)
	{
		lvl_player.kill();
		return false;
	}

	//Move monster
	if(current_time > next_monster_move)
	{
		move_monsters();
		next_monster_move = current_time+150;
	}

	lvl_player.render(pRenderer);
	return true;
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
	Mix_PlayChannel(-1, lvl_door_open, 0);
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

//Handle SDL events 
void Level::on_event(SDL_Event* pEvent)
{
	switch(pEvent->type)
	{
		case SDL_KEYDOWN:
			switch(pEvent->key.keysym.sym)
			{
				case SDLK_LEFT:
					lvl_player.move_x(-1);
					if(check_ground_collision() == true)
					{
						lvl_player.move_x(1);
					}
					break;
				case SDLK_RIGHT:
					lvl_player.move_x(1);
					if(check_ground_collision() == true)
					{
						lvl_player.move_x(-1);
					}
					break;
				case SDLK_UP:
					lvl_player.move_y(-2);
					if(check_ground_collision() == true)
					{
						lvl_player.move_y(1);
					}
					else
					{
						lvl_player.jump();
					}
					break;
			}
			break;
	}
}	
