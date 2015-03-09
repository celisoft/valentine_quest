#ifndef MENU_H
#define MENU_H

#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

class Menu
{
	private:
		SDL_Surface* bg_image;
		SDL_Texture* bg_texture;

		SDL_Rect bg_rect;

	public:
		Menu()
		{
			bg_rect.w = 1024;
			bg_rect.h = 768;
			bg_rect.x = 0;
			bg_rect.y = 0;
		}

		//Create the texture from surface
		bool load(SDL_Renderer* pRenderer, std::string pPath);

		//Unload the menu
		void dispose();

		//Display the menu
		void display(SDL_Renderer* pRenderer);

		//On event
		bool check_event(SDL_Event* pEvent);
};

#endif
