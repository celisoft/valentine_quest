#include "heart.h"

//Render the texture through given renderer
void Heart::render(SDL_Renderer* pRenderer)
{
	heart_texture = SDL_CreateTextureFromSurface(pRenderer, heart_image);
	SDL_RenderCopy(pRenderer, heart_texture, &sprite_rect, &heart_rect);
}

//Set player position to the given one
void Heart::set_pos(Position pPosition)
{
	pos = pPosition;

	heart_rect.x = pPosition.get_x() * 64;
	heart_rect.y = pPosition.get_y() * 64;
}

