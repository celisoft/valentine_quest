#include "menu.h"

bool Menu::load(SDL_Renderer* pRenderer)
{
	char* path = SDL_GetBasePath();
	std::string base_path = SDL_strdup(path);
	SDL_free(path);

	//Initialize background texture
	bg_image = IMG_Load((base_path + "assets/splashscreen.png").c_str());
	bg_texture = SDL_CreateTextureFromSurface(pRenderer, bg_image);
	if(bg_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(bg_image);

	return true;
}

void Menu::display(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, bg_texture, &bg_rect, &bg_rect);	
}

//Handle SDL events 
bool Menu::check_event(SDL_Event* pEvent)
{
	bool ret_val = false;
	switch(pEvent->type)
	{
		case SDL_KEYDOWN:
			ret_val = true;
			break;
	}
	return ret_val;
}	
