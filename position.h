#ifndef POSITION_H
#define POSITION_H

class Position
{
 	int coord_x;
      	int coord_y;	

	public:
		static const int MIN_X = 0;
		static const int MAX_X = 16;
		static const signed int MIN_Y = 0;
		static const int MAX_Y = 12;

		//Constructor
		Position(int pX=0, int pY=0)
		{
			set_x(pX);
			set_y(pY);
		}

		//Getters
		int get_x();
		int get_y();

		//Setters
		void set_x(int pX);
		void set_y(int pY);
};

#endif
