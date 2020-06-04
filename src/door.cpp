#include "door.hpp"

// Initialize texture
bool Door::init_texture(SDL_Renderer* pRenderer) {
	door_texture = SDL_CreateTextureFromSurface(pRenderer, door_image);
	if(door_texture <= 0) {
		return false;
	}
	SDL_FreeSurface(door_image);
	return true;
}

// Render the texture through given renderer
void Door::render(SDL_Renderer* pRenderer) {
	if(is_open) {
		sprite_rect.x = 128;
	}
	SDL_RenderCopy(pRenderer, door_texture, &sprite_rect, &door_rect);
}
