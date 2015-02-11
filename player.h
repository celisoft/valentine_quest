#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player
{
 	int score;  
	Position pos;
	SDL_Surface* player_image;	
	SDL_Texture* player_texture;
	SDL_Rect sprite_rect;
	SDL_Rect player_rect;

	public:
		//Constant initialization
		static const int LEFT_POS = 1;
		static const int RIGHT_POS = 0;
		static const int STEP_X = 64;
		static const int STEP_Y = 64;

		//Constructor
		Player()
		{
			score = 0;
			pos = Position(0, 0);

			player_image = IMG_Load("assets/players/aqualienne.png");

			sprite_rect.w = 32;
			sprite_rect.h = 64;
			sprite_rect.x = 32 * RIGHT_POS;
			sprite_rect.y = 0;

			player_rect.w = 32;
			player_rect.h = 64;
			player_rect.x = pos.get_x();
			player_rect.y = pos.get_y();
		}

		//Getter for player_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &player_rect; }

		//Set the player position to the given position
		void set_pos(Position pPosition);

		//Increase score
		void increase_score(){ score++; }
		
		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Move on X axis 
		void move_x(int step);

		//Move on Y axis
		void move_y(int step);
};

#endif
