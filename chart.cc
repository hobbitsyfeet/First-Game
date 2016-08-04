
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


Chart::Chart(){

}
void Chart::loadWorld(string name){
	//INITIALISATION
	vector<vector<container> >::iterator row;
	vector<container>::iterator col;
	//type of block to set it as
	container block, block_reset;
	char inChar;
	int x, y;
	int posXPortal = -1,posYPortal = -1,numPortal;
	string option ="";
	//END OF INITIALIZATION;
	//set name of loaded world
	//this->worldName = name;

	ifstream fin;
	fin.open(("./maps/" + name + ".txt").c_str());
	while(fin.fail()){
		cout<<"invalid file, enter a file>> ";
		cin>>name;
		fin.open(("./maps/" + name + ".txt").c_str());
	}
		cout<<"Loading map..."<<endl;
	this->worldName = name;
	fin>>x>>y;
	//creates 2D vector of size x,y
	world.resize(x, vector<container> (y) );

	//number or portals in a map
	option="";
	fin>>numPortal;
	for(int i = 0; i<numPortal; i++){
		fin>>posXPortal>>posYPortal>>option;
	}
	cout<<posXPortal<<posYPortal<<endl;
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

			if( (posXPortal == x) && (posYPortal == y) ){
				block.link = option;
				cout<<"!";
			}
			else{
				block.link = "";
			}
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
			if(col->getGeoType()=='-')
				cout<<' ';
			else
				col->displayType();
		//cout<<col->getOccupance();
			cout<<col->getLink();
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
    +  ( col->getPosY() - centrePosY)*(col->getPosY() - centrePosY) );
  		if(dist <= radius){
  			if(centrePosX == col->getPosX() && centrePosY == col->getPosY())
  				cout<<"P ";
  			else{
					if(col->getGeoType()=='-')
						cout<<' ';
					else
						col->displayType();
					cout<<' ';
				}
			}
			else
				cout<<"# ";
		}
		cout<<endl;
	}
}

bool Chart::canEnter(int x, int y){
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
}

void Chart::searchFor(char spawnPt, int& x, int&y){
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

void Chart::isPortal(int x,int y){
	cout<<"starting portal search"<<endl;
	vector<vector <container> >::iterator row = world.end()-y;
	vector<container> ::iterator col = row->begin()+x-1;
	cout<<col->getPosX()<<col->getPosY()<<col->getLink();
	if(col->getLink() != ""){
		this->loadWorld(col->getLink().c_str());
		cout<<"going to"<< col->getLink();
	}
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
