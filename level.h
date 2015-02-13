#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <fstream>
#include <string>
#include <vector>

#include "position.h"
#include "monster.h"

using namespace std;

class Level
{
	private:
		SDL_Surface* bg_image;
		SDL_Texture* bg_texture;

		SDL_Surface* lvl_image;	
		SDL_Texture* lvl_texture;
		SDL_Rect sprite_rect;
		SDL_Rect bg_rect;

		vector<SDL_Rect> lvl_ground;
		vector<Monster> lvl_monsters; 

		Position start_pos;

		Mix_Music* lvl_music;

		//Add rect to lvl_ground vector
		void add_rect(int pX, int pY);

		//Generate new monster
		void create_monster(int pXmin, int pXmax, int pY);

	public:
		//Constructor
		Level(string pLvlMapPath, string pLvlGroundPath)
		{
			lvl_image = IMG_Load(pLvlGroundPath.c_str());
			bg_image = IMG_Load("assets/backgrounds/bg_nuagafille.png");

			//Initialize the bg sprite
			bg_rect.w = 1024;
			bg_rect.h = 768;
			bg_rect.x = 0;
			bg_rect.y = 0;

			//Initialize the ground sprite
			sprite_rect.w = 64;
			sprite_rect.h = 64;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			//TODO Externalize
			//Initialize the different rect to be identified as ground rect
			ifstream lvl_file(pLvlMapPath);
			if(lvl_file.is_open())
			{
				string line;
				int monster_x1{0};
				int monster_x2{0};

				float line_idx{0};
				float col_idx{0};

				while(getline(lvl_file, line))
				{
					for(auto lChar : line)
					{
						switch(lChar)
						{
							case '*':
								add_rect(col_idx, line_idx);
								break;
							case 'P':
								start_pos = Position(col_idx, line_idx);
								break;
							case '[':
								monster_x1 = col_idx;
								break;
							case ']':
								monster_x2 = col_idx;
								break;
						}
						col_idx++;
					}
					
					if(monster_x1 != monster_x2)
					{
						create_monster(monster_x1, monster_x2, line_idx);
					}

					monster_x1 = 0;
					monster_x2 = 0;
					col_idx = 0;
					line_idx++;
				}
			}
			//TODO rise an exception
			//else
			//{
			//}
			lvl_file.close();

			//Initialize the sound
			lvl_music = Mix_LoadMUS("assets/sfx/musique_aqua.ogg");
		}
		
		//Getter for player start position
		Position get_player_start_position(){return start_pos;}

		//Initialize the texture to be rendered
		bool init_textures(SDL_Renderer* pRenderer);

		//Launch the music
		void play_bg_music();

		//Move monsters :D
		void move_monsters();

		//Check for collision with a given SDL_Rect
		bool check_ground_collision(SDL_Rect* pPlayer);

		//Check for collision between player_rect and monsters
		bool check_monster_collision(SDL_Rect* pPlayer);

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);
};

#endif
