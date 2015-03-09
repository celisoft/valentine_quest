#ifndef HEART_H
#define HEART_H

#include "position.h"
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include <string>

class Heart
{
	private:
		Position pos;
		SDL_Surface* heart_image;	
		SDL_Texture* heart_texture;
		SDL_Rect sprite_rect;
		SDL_Rect heart_rect;

		bool is_visible = false;
		bool is_eaten = false;

	public:
		//Constructor
		Heart(std::string pPath, int pX, int pY)
		{
			pos = Position(pX, pY);

			heart_image = IMG_Load((pPath + "heart.png").c_str());

			sprite_rect.w = 64;
			sprite_rect.h = 64;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			heart_rect.w = sprite_rect.w;
			heart_rect.h = sprite_rect.h;
			heart_rect.x = pos.get_x() * 64;
			heart_rect.y = pos.get_y() * 64;
		}

		//Set visible
		void set_visibility(bool pVal){is_visible = pVal;}

		//Get visibility
		bool get_visibility(){return is_visible;}

		//Eat the heart
		void eat(){is_eaten = true;};

		//Get eaten status
		bool is_eat(){return is_eaten;}

		//Getter for heart_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &heart_rect; }

		//Set the player position to the given position
		void set_pos(Position pPosition);
	
		//Load the texture
		bool init_texture(SDL_Renderer* pRenderer);

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Destroy
		void dispose();
};

#endif
