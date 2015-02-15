#include "player.h"

//Initialize texture
bool Player::init_texture(SDL_Renderer* pRenderer)
{
	player_texture = SDL_CreateTextureFromSurface(pRenderer, player_image);
	if(player_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(player_image);
	return true;
}

//Render the texture through given renderer
void Player::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, player_texture, &sprite_rect, &player_rect);
}

//Set player position to the given one
void Player::set_pos(Position pPosition)
{
	pos = pPosition;
	player_rect.x = pPosition.get_x() * STEP_X;
	player_rect.y = pPosition.get_y() * STEP_Y;
}

//Move on X axis with a default step of 1
void Player::move_x(int step=1)
{
	pos.set_x(pos.get_x()+step);

	//Update player sprite
	if(step < 0)
	{
		if(sprite_rect.x == 32*LEFT_POS_0)
		{
			sprite_rect.x = 32*LEFT_POS_1;
		}
		else
		{
			sprite_rect.x = 32*LEFT_POS_0;
		}
	}
	else
	{
		if(sprite_rect.x == 32*RIGHT_POS_0)
		{
			sprite_rect.x = 32*RIGHT_POS_1;
		}
		else
		{
			sprite_rect.x = 32*RIGHT_POS_0;
		}
	}

	//Update player_rect with updated X
	player_rect.x = pos.get_x() * STEP_X;
}

//Move on Y axis with a default step of 1
void Player::move_y(int step=1)
{
	pos.set_y(pos.get_y()+step);

	//Update player_rect with updated Y
	player_rect.y = pos.get_y() * STEP_Y;
}


