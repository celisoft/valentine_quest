#ifndef HEART_H
#define HEART_H

#include "position.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Heart
{
	private:
		Position pos;
		SDL_Surface* heart_image;	
		SDL_Texture* heart_texture;
		SDL_Rect sprite_rect;
		SDL_Rect heart_rect;

	public:
		//Constructor
		Heart(int pX, int pY)
		{
			pos = Position(pX, pY);

			heart_image = IMG_Load("assets/heart.png");

			sprite_rect.w = 64;
			sprite_rect.h = 64;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			heart_rect.w = sprite_rect.w;
			heart_rect.h = sprite_rect.h;
			heart_rect.x = pos.get_x() * 64;
			heart_rect.y = pos.get_y() * 64;
		}

		//Destructor
		//~Heart()
		//{
		//	SDL_FreeSurface(heart_image);
		//	SDL_DestroyTexture(heart_texture);
		//}

		//Getter for heart_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &heart_rect; }

		//Set the player position to the given position
		void set_pos(Position pPosition);
		
		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

};

#endif
