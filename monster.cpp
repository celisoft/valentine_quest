#include "monster.h"
#include <iostream>

//Render the texture through given renderer
void Monster::render(SDL_Renderer* pRenderer)
{
	monster_texture = SDL_CreateTextureFromSurface(pRenderer, monster_image);
	SDL_RenderCopy(pRenderer, monster_texture, &sprite_rect, &monster_rect);
}

//Set player position to the given one
void Monster::set_pos(Position pPosition)
{
	pos = pPosition;

	monster_rect.x = pPosition.get_x() * STEP_X;
	monster_rect.y = pPosition.get_y() * STEP_Y;

}

//Move the monster and refresh its surface
void Monster::move()
{
	int x_val{0};
	int y_val{pos.get_y()};

	if(direction == RIGHT)
	{
		std::cout << "RIGHT" << pos.get_x() << std::endl;
		if(pos.get_x() < x_max)
		{
			x_val = pos.get_x() + 1;
			set_pos(Position(x_val, y_val));
		}
		else
		{
			direction = LEFT;
		}

		if(sprite_rect.x == RIGHT_POS_0)
		{
			sprite_rect.x = RIGHT_POS_1;
		}
		else
		{
			sprite_rect.x = RIGHT_POS_0;
		}
	}
	else
	{
		std::cout << "LEFT" << pos.get_x() << std::endl;
		if(pos.get_x() > x_min)
		{
			x_val = pos.get_x() - 1;
			set_pos(Position(x_val, y_val));
		}
		else
		{
			direction = RIGHT;
		}

		if(sprite_rect.x == LEFT_POS_0)
		{
			sprite_rect.x = LEFT_POS_1;
		}
		else
		{
			sprite_rect.x = LEFT_POS_0;
		}
	}
}

