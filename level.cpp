#include "level.h"
#include <iostream>

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

//Generate new monster
void Level::create_monster(int pXmin, int pXmax, int pY)
{
	lvl_monsters.push_back(Monster(pXmin, pXmax, pY));
}

//Move monsters :D
void Level::move_monsters()
{
	for(auto& lMonster : lvl_monsters)
	{
		std::cout << lMonster.get_rect()->x << std::endl;
		lMonster.move();
		std::cout << lMonster.get_rect()->x << std::endl;
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
}

