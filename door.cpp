#include "door.h"

//Render the texture through given renderer
void Door::render(SDL_Renderer* pRenderer)
{
	if(is_visible)
	{
		door_texture = SDL_CreateTextureFromSurface(pRenderer, door_image);
		SDL_RenderCopy(pRenderer, door_texture, &sprite_rect, &door_rect);
	}
}
