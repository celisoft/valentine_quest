#include "game_window.hpp"

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

// Initialize an 1024x768 SDL window
bool GameWindow::init() {
	// Try to initailize all SDL component and check if it works
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS) < 0) {
		return false;
	}

	// Create a window and check if it works
	display = SDL_CreateWindow("Xylandia - Valentine Quest",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		       	1024, 768, SDL_WINDOW_OPENGL);

	if(display == nullptr) {
		return false;
	}

	// Create the renderer
	renderer = SDL_CreateRenderer(display, -1, 0);
	if(renderer == nullptr) {
		return false;
	}

	// Initialize SDL_Mixer
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0) {
		return false;
	}

	// Initialize base path
	char* path = SDL_GetBasePath();
	if(path == nullptr) {
		base_path = SDL_strdup("./");
	} else {
		base_path = SDL_strdup(path);
		SDL_free(path);
	}
	return true;
}

bool GameWindow::run() {
	is_running = init();
	if(is_running == false) {
		// Init phase fails
		return false;
	}

	if(!menu.load(renderer, base_path)) {
		return false;
	}

	if(!lvl_manager.load_index(renderer, base_path)) {
		return false;
	}

	SDL_Event lEvent;

	while(is_running) {
		SDL_RenderClear(renderer);

		if(!is_playing) {
			menu.display(renderer);
		} else {
			is_playing = lvl_manager.display(renderer);
		}

		if(SDL_PollEvent(&lEvent)) {
			on_event(&lEvent);
			if(!is_playing) {
				is_playing = menu.check_event(&lEvent);
			} else {
				lvl_manager.on_event(&lEvent);
			}
		}

		SDL_RenderPresent(renderer);

		// Slow down cycles
		SDL_Delay(16);
	}

	// Dispose menu and level_manager memory
	menu.dispose();

	// Display the user an happy ending
	SDL_Surface* ending_image = IMG_Load((base_path + "assets/happyend.png").c_str());
	SDL_Texture* ending_texture = SDL_CreateTextureFromSurface(renderer, ending_image);
	SDL_FreeSurface(ending_image);

	SDL_Rect ending_rect;
	ending_rect.w = 1024;
	ending_rect.h = 768;
	ending_rect.x = 0;
	ending_rect.y = 0;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, ending_texture, &ending_rect, &ending_rect);
	SDL_RenderPresent(renderer);

	// Slow down cycles
	SDL_Delay(1800);

	SDL_DestroyTexture(ending_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(display);
	Mix_CloseAudio();
	SDL_Quit();
	return true;
}

// Handle SDL events
void GameWindow::on_event(SDL_Event* pEvent) {
	switch(pEvent->type) {
		case SDL_QUIT:
			is_running = false;
			break;
	}
}

