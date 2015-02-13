#include "game_window.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

//Initialize an 1024x768 SDL window
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
	
	return true;
}

void GameWindow::player_fall_down()
{
	player->move_y(1);
	if(current_lvl->check_ground_collision(player->get_rect()) == true)
	{
		player->move_y(-1);
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
		
	SDL_Event lEvent;
	int current_time{0};
	int next_fall_down{0};
	int next_monster_move{0};

	while(is_running)
	{
		current_lvl = lvl_manager.get_current_level(renderer);
		player = current_lvl->get_player();
		if(current_lvl->is_finished())
		{
			if(!lvl_manager.prepare_next_level(renderer))
			{
				is_running = false;
			}
		}
		else
		{
			SDL_RenderClear(renderer);
		
			current_time = SDL_GetTicks();

			//Simulate gravity
			if(current_time > next_fall_down)
			{
				player_fall_down();
				next_fall_down = current_time+80;
			}

			if(current_lvl->check_heart_collision())
			{
				if(current_lvl->get_remaining_hearts() == 0)
				{
					is_running = false;
					//current_lvl->show_door();
				}
				else
				{
					current_lvl->set_random_heart_visible();
				}
			}

			//End the game if the player is killed	
			if(current_lvl->check_monster_collision(player->get_rect()) == true)
			{
				player->kill();
				is_running = false;
			}

			//Move monster
			if(current_time > next_monster_move)
			{
				current_lvl->move_monsters();
				next_monster_move = current_time+150;
			}

			if(SDL_PollEvent(&lEvent))
			{
				on_event(&lEvent);
			}

			current_lvl->render(renderer);
			player->render(renderer);

			SDL_RenderPresent(renderer);

			//Slow down cycles
			SDL_Delay(16);
		}
	}

	//Display the user an happy ending or not
	SDL_Surface* ending_image = IMG_Load("assets/happyend.png");
	if(player->is_alive() == false)
	{
		ending_image = IMG_Load("assets/gameover.png");
	}
	SDL_Texture* ending_texture = SDL_CreateTextureFromSurface(renderer, ending_image);	
	SDL_FreeSurface(ending_image);
	
	SDL_Rect ending_rect;
	ending_rect.w = 1024;
	ending_rect.h = 768;
	ending_rect.x = 0;
	ending_rect.y = 0;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, ending_texture, &ending_rect, &ending_rect); 
	SDL_RenderPresent(renderer);

	//Slow down cycles
	SDL_Delay(1500);

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
					player->move_x(-1);
					if(current_lvl->check_ground_collision(player->get_rect()) == true)
					{
						player->move_x(1);
					}
					break;
				case SDLK_RIGHT:
					player->move_x(1);
					if(current_lvl->check_ground_collision(player->get_rect()) == true)
					{
						player->move_x(-1);
					}
					break;
				case SDLK_UP:
					player->move_y(-2);
					if(current_lvl->check_ground_collision(player->get_rect()) == true)
					{
						player->move_y(1);
					}
					break;
			}
			break;
		case SDL_QUIT:
			is_running = false;
			break;
	}
}	

