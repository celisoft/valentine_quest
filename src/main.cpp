/**
 * This code is using C++11.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "game_window.hpp"
#undef main

int main() {
	GameWindow lWindow;
	if(lWindow.run() == false) {
		std::cerr << "Cannot initialize a SDL game window !" << std::endl;
	}

	return 0;
}
