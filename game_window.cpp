#include "game_window.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

//Initialize an 800x600 SDL window
bool GameWindow::init()
{
	//Try to initailize all SDL component and check if it works
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	//Create a window and check if it works
	display = SDL_CreateWindow("Xylandia - Valentine Quest",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		       	1024, 768, SDL_WINDOW_OPENGL);
	
	if(display == nullptr)
	{
		return false;
	}

	//Create the renderer
	renderer = SDL_CreateRenderer(display, -1, 0);
	if(renderer == nullptr)
	{
		return false;
	}

	//Initialize SDL_Mixer
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
	{
		return false;
	}

	//Initialize level texture
	bool lvl_init = lvl.init_textures(renderer); 
	if(lvl_init == false)
	{
		return false;
	}

	return true;
}

void GameWindow::player_fall_down()
{
	player.move_y(1);
	if(lvl.check_ground_collision(player.get_rect()) == true)
	{
		player.move_y(-1);
	}
}

bool GameWindow::run()
{
	is_running = init();
	if(is_running == false)
	{
		//Init phase fails
		return false;
	}

	//Play background music
	lvl.play_bg_music();
	
	SDL_Event lEvent;
	int current_time{0};
	int next_fall_down{0};
	int next_monster_move{0};

	while(is_running)
	{		
		SDL_RenderClear(renderer);
		
		current_time = SDL_GetTicks();

		//Simulate gravity
		if(current_time > next_fall_down)
		{
			player_fall_down();
			next_fall_down = current_time+80;
		}
	
		if(lvl.check_monster_collision(player.get_rect()) == true)
		{
			//TODO game over but not quit !!
			is_running = false;
		}

		//Move monster
		if(current_time > next_monster_move)
		{
			lvl.move_monsters();
			next_monster_move = current_time+150;
		}

		if(SDL_PollEvent(&lEvent))
		{
			on_event(&lEvent);
		}

		lvl.render(renderer);
		player.render(renderer);

		SDL_RenderPresent(renderer);

		//Slow down cycles
		SDL_Delay(16);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(display);
	Mix_CloseAudio();
	SDL_Quit();
	return true;
}

//Handle SDL events 
void GameWindow::on_event(SDL_Event* pEvent)
{
	switch(pEvent->type)
	{
		case SDL_KEYDOWN:
			switch(pEvent->key.keysym.sym)
			{
				case SDLK_LEFT:
					player.move_x(-1);
					if(lvl.check_ground_collision(player.get_rect()) == true)
					{
						player.move_x(1);
					}
					break;
				case SDLK_RIGHT:
					player.move_x(1);
					if(lvl.check_ground_collision(player.get_rect()) == true)
					{
						player.move_x(-1);
					}
					break;
				case SDLK_UP:
					player.move_y(-2);
					if(lvl.check_ground_collision(player.get_rect()) == true)
					{
						player.move_y(1);
					}
					break;
			}
			break;
		case SDL_QUIT:
			is_running = false;
			break;
	}
}	

