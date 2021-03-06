#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include "position.hpp"
#include "monster.hpp"
#include "player.hpp"
#include "heart.hpp"
#include "door.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

class Level {
	private:
		int current_time{0};
		int next_fall_down{0};
		int next_monster_move{0};

		std::string lvl_bg_path;
		std::string lvl_ground_path;
		std::string lvl_music_path;
		std::string lvl_map_path;
		std::string lvl_player_path;
		std::string lvl_door_path;
		std::string lvl_asset_path;

		SDL_Surface* bg_image;
		SDL_Texture* bg_texture;

		SDL_Surface* lvl_image;
		SDL_Texture* lvl_texture;
		SDL_Rect sprite_rect;
		SDL_Rect bg_rect;

		std::vector<SDL_Rect> lvl_ground;
		std::vector<Monster> lvl_monsters;
		std::vector<Heart> lvl_hearts;

		Player lvl_player;
		Door lvl_door;

		Mix_Music* lvl_music;
		Mix_Chunk* lvl_beep;
		Mix_Chunk* lvl_door_open;

		// Add rect to lvl_ground vector
		void add_rect(int pX, int pY);

		// Generate new monster
		void create_monster(int pXmin, int pXmax, int pY);

		// Create heart
		void create_heart(int pX, int pY);

		// Load the level map
		bool load_map(std::string pMapFilepath);

		// Indicator if level is loaded
		bool is_load = false;

		// Indicator if level is finished
		bool is_finish = false;

	public:
		// Constructor
		Level(std::string pBgPath, std::string pGroundPath, std::string pBgMusicPath,
				std::string pMapPath, std::string pPlayerPath, std::string pDoorPath,
				std::string pAssetPath) {
			lvl_bg_path = pBgPath;
			lvl_ground_path = pGroundPath;
			lvl_music_path = pBgMusicPath;
			lvl_map_path = pMapPath;
			lvl_player_path = pPlayerPath;
			lvl_door_path = pDoorPath;
			lvl_asset_path = pAssetPath;
		}

		// Load the level
		bool load(SDL_Renderer* pRenderer);

		// Unload the level (cleanup memory)
		void unload();

		// Unifnish the level
		void unfinish() {is_finish = false;}

		// Getter for is_finished indicator
		bool is_finished() {return is_finish;}

		// Getter for is_loaded indicator
		bool is_loaded() {return is_load;}

		// Initialize the texture to be rendered
		bool init_textures(SDL_Renderer* pRenderer);

		// Launch the music
		void play_bg_music();

		// Move monsters :D
		void move_monsters();

		// Check for collision with a given SDL_Rect
		bool check_ground_collision();

		// Check for collision between player_rect and monsters
		bool check_monster_collision();

		// Check for collisiob between player_rect and heart
		bool check_heart_collision();

		// Check for collision between player_rect and door
		bool check_door_collision();

		// Return the number of heart that were not eaten
		int get_remaining_hearts();

		// Open the level door
		void open_door();

		// Generate random number between pMin & pMax
		int get_random(int pMin, int pMax);

		// Show an heart randomly
		void set_random_heart_visible();

		// Render the texture through given renderer
		bool render(SDL_Renderer* pRenderer);

		// event catcher
		void on_event(SDL_Event* pEvent);
};

#endif  // LEVEL_HPP_
