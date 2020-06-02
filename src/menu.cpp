#include "menu.hpp"

bool Menu::load(SDL_Renderer* pRenderer, std::string pPath)
{	
	//Initialize background texture
	bg_image = IMG_Load((pPath + "assets/splashscreen.png").c_str());
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

void Menu::dispose()
{
	SDL_DestroyTexture(bg_texture);
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
