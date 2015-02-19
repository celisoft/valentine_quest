/**
 * This code is using C++11.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "game_window.h"

using namespace std;

int main()
{
	GameWindow lWindow;
	if(lWindow.run() == false)
	{
		cerr << "Cannot initialize a SDL game window !" << endl;
	}

	return 0;
}
