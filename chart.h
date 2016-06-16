#ifndef CHART_H
#define CHART_H

//#include "unit.h"
//#include "turn.h"
using namespace std;

class Chart{
	private:

		class container{
			friend class Chart;
		public:
			//container();
		//contains
			bool canEnter(int,int);
			bool checkAvailable();
			bool getOccupance();
			char getGeoType();
			void displayType();
			int getPosX();
			int getPosY();
		private:
			int posX, posY;
			bool occupied;
			char geoType;
	};
	//2D vector
	vector< vector<container> > world; 
	string worldName;
	public:

	Chart();
	void displayWorld();
	void loadWorld(string);
	void saveWorld(string);
	bool canEnter(int,int);
	void searchFor(char, int&, int&);
	//void playWorld();
};

#endif
