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
	//int lvlmap[12][16] {{0}};
	
	//ifstream fic("test.lvlmap");
	//if(fic.is_open())
	//{
	//	string line;
	//	int line_idx = 0;
	//	int col_idx = 0;
//
//		while(getline(fic, line))
//		{
//			for(auto lChar : line)
//			{
//				if(lChar == '*')
//				{
//					lvlmap[line_idx][col_idx] = 1;
//				}
//				col_idx++;
//			}
//			col_idx = 0;
//			line_idx++;
//		}
//		fic.close();
//		cout << "Level is loaded !" << endl;
//	}
//	else
//	{
//		cerr << "Cannot read the level map" << endl;
//	}
 
	GameWindow lWindow;
	if(lWindow.run() == false)
	{
		cerr << "Cannot initialize a SDL game window !" << endl;
	}

	return 0;
}
