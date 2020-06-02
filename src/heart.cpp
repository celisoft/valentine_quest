#include "heart.hpp"

bool Heart::init_texture(SDL_Renderer* pRenderer)
{
	heart_texture = SDL_CreateTextureFromSurface(pRenderer, heart_image);
	if(heart_texture == nullptr)
	{
		return false;
	}
	SDL_FreeSurface(heart_image);
	return true;
}

//Render the texture through given renderer
void Heart::render(SDL_Renderer* pRenderer)
{
	if(is_visible)
	{
		SDL_RenderCopy(pRenderer, heart_texture, &sprite_rect, &heart_rect);
	}
}

//Set player position to the given one
void Heart::set_pos(Position pPosition)
{
	pos = pPosition;

	heart_rect.x = pPosition.get_x() * 64;
	heart_rect.y = pPosition.get_y() * 64;
}

//Destroy
void Heart::dispose()
{
	SDL_DestroyTexture(heart_texture);	
}
