#ifndef DOOR_HPP_
#define DOOR_HPP_

#include "position.hpp"

#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include <string>

class Door {
	private:
		Position pos;
		SDL_Surface* door_image;
		SDL_Texture* door_texture;
		SDL_Rect sprite_rect;
		SDL_Rect door_rect;
		bool is_open = false;

	public:
		// Constructor
		explicit Door(std::string pDoorPath = "", int pX = 0, int pY = 0) {
			pos = Position(pX, pY);

			door_image = IMG_Load(pDoorPath.c_str());

			sprite_rect.w = 128;
			sprite_rect.h = 128;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			door_rect.w = sprite_rect.w;
			door_rect.h = sprite_rect.h;
			door_rect.x = pos.get_x() * 64;
			door_rect.y = pos.get_y() * 64;
		}

		// Open the door
		void open() {is_open = true;}

		// Return boolean value indicating if the door is open
		bool is_opened() {return is_open;}

		// Getter for door_rect (will be used for collsion)
		SDL_Rect* get_rect() { return &door_rect; }

		// Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		// Initialize texture
		bool init_texture(SDL_Renderer* pRenderer);

		// Getter for door texture
		SDL_Texture* get_texture() {return door_texture;}
};

#endif  // DOOR_HPP_
