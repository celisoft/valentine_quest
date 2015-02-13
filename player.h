#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Player
{
 	int score;  
	Position pos;
	SDL_Surface* player_image;	
	SDL_Texture* player_texture;
	SDL_Rect sprite_rect;
	SDL_Rect player_rect;
	bool is_dead = false;

	public:
		//Constant initialization
		static const int LEFT_POS_0 = 3;
		static const int LEFT_POS_1 = 2;
		static const int RIGHT_POS_0 = 0;
		static const int RIGHT_POS_1 = 1;
		static const int STEP_X = 64;
		static const int STEP_Y = 64;

		//Constructors
		Player(string pSpritePath="", int pX=0, int pY=0)
		{
			score = 0;
			pos = Position(pX, pY);

			player_image = IMG_Load(pSpritePath.c_str());

			sprite_rect.w = 32;
			sprite_rect.h = 64;
			sprite_rect.x = 32 * RIGHT_POS_0;
			sprite_rect.y = 0;

			player_rect.w = 32;
			player_rect.h = 64;
			player_rect.x = pX * STEP_X;
			player_rect.y = pY * STEP_Y;
		}

		//Getter for player_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &player_rect; }

		//Set the player position to the given position
		void set_pos(Position pPosition);

		//Kill the player
		void kill(){is_dead = true;}

		//Check if player is alive
		bool is_alive(){return !is_dead;}

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
