
#include <vector>
#include<fstream>
//#include <ifstream>
//#include <ofstream>
#include <iostream>
#include <cmath>
#include "turn.h"
#include "unit.h"
#include "chart.h"
using namespace std;

/*
Chart::Chart(string ChartName,int ChartWidth, int chartHeight, bool FoW){
	chartWidth = ChartWidth;
	chartHeight = ChartHeight;
	fogOfWar = FoW;
	chartName = ChartName;
}*/


void Chart::loadWorld(string name){
	//INITIALISATION
	vector<vector<container> >::iterator row;
	vector<container>::iterator col;
	//type of block to set it as
	container block, block_reset;
	char inChar;
	int x, y, i;
	int posXPortal = 0,posYPortal = 0,numPortal;
	string option ="";
	//END OF INITIALIZATION;
	//set name of loaded world
	//this->worldName = name;

	ifstream fin;
	fin.open(("./maps/" + name + ".txt").c_str());
	//Prevent crash by selecting an existing file
	while(fin.fail()){
		cout<<"invalid file, enter a file>> ";
		cin>>name;
		fin.open(("./maps/" + name + ".txt").c_str());
	}

		cout<<"Loading map..."<<endl;
	this->worldName = name;
	fin>>x>>y;

	//creates 2D vector of size x,y
	world.clear();
	world.resize(x, vector<container>(y));

	fin>>fogOfWar;
	//number or portals in a map
	option="";
	fin>>numPortal;
	//arrays for multiple portals
	int portalx [numPortal];
	int portaly [numPortal];
	string portalNames[numPortal];

	//setting portal name and coords into arrays
	for(int i = 0; i<numPortal; i++){
		fin>>posXPortal>>posYPortal>>option;
		portalx[i] = posXPortal;
		portaly[i]=posYPortal;
		portalNames[i] = option;
	}

	//iterates through and sets type
	x=1;
	for(row = world.begin(); row < world.end() ; row++){
		for(col = row->begin(); col< row->end(); col++){
			//gets type
			fin.ignore();
			fin>>block.geoType;
			if(block.checkAvailable()==true)
			block.occupied=false;
			else
			block.occupied=true;

			//portal
			//for(int i = 0; i<numPortal; i++){
				if( (portalx[i] == x) && (portaly[i] == y) ){
					block.link = portalNames[i];
					//NOTE::::Must list links in order of top
					//left to bottom right
					//because it does not repeat i in a loop;
					i++;
				}
				else{
					block.link = "";
				}
		//	}

			block.posX = x;
			block.posY = y;
			*col= block;
			block = block_reset;


			x++;
		}
		x=1;
		y--;
	}
	fin.close();
	cout<<"Done Loading."<<endl;

}



void Chart::displayWorld(){
	vector<vector<container> >::iterator row;
	vector<container>::iterator col;
	for(row = world.begin(); row < world.end() ; row++){
		for(col = row->begin(); col < row->end(); col++){
			if(col->getGeoType()=='-' || col->getGeoType() =='O')
				cout<<"  ";
			else{
				col->displayType();
				cout<<' ';
			}
		//cout<<col->getOccupance();
		//	cout<<col->getLink();
		}
		cout<<endl;
	}
}

void Chart::displayRange(int centrePosX,int centrePosY, int radius){

	vector<vector<container> >::iterator row;
	vector<container>::iterator col;
	int dist;
	for(row = world.begin(); row < world.end() ; row++){
		for(col = row->begin(); col < row->end(); col++){
 			 dist = sqrt( ( (col->getPosX() - centrePosX)*(col->getPosX() - centrePosX) )
   		 + 	 ( col->getPosY() - centrePosY)*(col->getPosY() - centrePosY) );

  

  		if(getFogOfWar()){
  			if(dist <= radius){
  			if(centrePosX == col->getPosX() && centrePosY == col->getPosY())
  			cout<<"P ";
  			else{
					if(col->getGeoType()=='-' || col->getGeoType() =='O')
						cout<<' ';
					else
						col->displayType();
					cout<<' ';
				}
			}
				else
					cout<<"- ";
		}
		else{
			if(centrePosX == col->getPosX() && centrePosY == col->getPosY())
  			cout<<"P ";

  			else{
				if(col->getGeoType()=='-' || col->getGeoType() =='O')
					cout<<"  ";
				else{
					col->displayType();
					cout<<' ';
					}
				}
			}
		}
		cout<<endl;
	}
}

bool Chart::canEnter(int x, int y){
	vector<vector <container> >::iterator row = world.end()-y;
	vector<container> ::iterator col = row->begin()+x-1;
	cout<<col->getPosX()<<','<<col->getPosY()<<endl;
	if(col->getOccupance() == false){
		cout<<"allowed to enter"<<endl;
		return false;
	}
	else return true;
	/*
	int i=1,j=1;
	//cout<<"starting canEnter";
	vector<vector <container> >::iterator row;
	vector<container> ::iterator col;
	for(row = world.begin(); row < world.end(); row++){
		for(col = row->begin(); col< row->end() ; col++){
			//cout<<i<<','<<j<<endl;
			//cout<<col->getOccupance()<<endl;
			if(i==x && j==y){
				if(col->getOccupance() == false){
					cout<<"testing occupance";
					if(col->getGeoType() == 'O')
						col->geoType = '-';
					return true;
				}
			}
			j++;
		}
		j=1;
		i--;
	}
	return false;
	*/
}

void Chart::setSpawn(char spawnPt, int& x, int&y){
	vector<vector <container> >::iterator row;
	vector<container> ::iterator col;
	for(row = world.begin(); row < world.end(); row++){
		for(col = row->begin(); col< row->end(); col++){
			if(spawnPt == col->getGeoType()){
				x = col->getPosX();
				y = col->getPosY();
				return;
			}
		}
	}
}

void Chart::findPath(int initX,int initY, int finX, int finY){
	//initialize
	vector<vector <container> >::iterator row = world.end()-initY;
	vector<container> ::iterator col = row->begin()+initX-1;
}

void Chart::isPortal(int x,int y,bool& gotLink){
	cout<<"starting portal search"<<endl;
	vector<vector <container> >::iterator row = world.end()-y;
	vector<container> ::iterator col = row->begin()+x-1;
	cout<<col->getPosX()<<col->getPosY()<<col->getLink();
	if(col->getLink() != ""){
		gotLink = true;
		this->loadWorld(col->getLink().c_str());
		cout<<"going to"<< col->getLink();
	}
}

bool Chart::getFogOfWar(){
	return fogOfWar;
}

void Chart::container::displayType(){
	cout<<geoType;
}

char Chart::container::getGeoType(){
	return geoType;
}
bool Chart::container::getOccupance(){
	return occupied;
}
int Chart::container::getPosX(){
	return posX;
}
int Chart::container::getPosY(){
	return posY;
}
string Chart::container::getLink(){
	return link;
}
bool Chart::container::checkAvailable(){
	//if not occupied check if terrain is accessible
	//if(this->getOccupance() == false)
		switch(this->getGeoType()){
			case'!':
			//case'@':
			case'$':
			case'%':
			case'^':
			case'&':
			case'*':
			case'~':
			case'#':
			case'|':
			case'_':
			return false;
				break;
			default:
				return true;
		}
		//else return false;
}
