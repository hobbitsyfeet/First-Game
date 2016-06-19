#ifndef UNIT_H
#define UNIT_H
#include "unit.h"
#include "item.h"
#include <iostream>
#include <vector>
using namespace std;

class Unit{
public:
//CONSTRUCTORS
	Unit(string="NoName", int=1,int =15,int=2, int=1,int=0, int=0,int=0, int = 6, int =0, int=0);

//*******Map_Position********
	int posX;
	int posY;
	void getPos();
	int getPosX();
	int getPosY();
	void distanceFromUnit();

//********I/O_Files************
	void loadUnit(string);//
	void saveUnit(string);//

//************get stats*********
	string getName()const;//
	int getLevel()const;//
	int getExp()const;//
	int getHealth()const;//
	int getDefence()const;//
	int getAttack()const;//
	int getGold()const;//
	int getStamina()const;//

	void displayStats();


//***********COMBAT*************
	void attackUnit(Unit&);//
	int distanceUnit(const Unit&);

//*********Inventory************
	struct inventory{
  	//main container for inventory
  	vector<Item> invContainer;
	
  	void loadInventory(string);//
  	void saveInventory(string);//
  
	  //functions for inventory
  	void pickUp(Item);//
 	 void dropItem(Item);
 	 bool search(const Item);//
	};
	//Unit's own inventory and function to display
	inventory inv;
	void displayInv();//

//******get Equipment***********
	void unEquipItem(string);
	void equipItem(string);//
	bool leftHandEquipped;
	bool rightHandEquipped;
	bool headEquipped;
	bool torsoEquipped;
	bool legsEquipped;
	bool feetEquipped;
	//************Operators************
	Unit& operator = (const Unit&);//
private:
	//*****Unit stats*****
	int health;
	int stamina;
	int attack;
	int defence;
	int gold;
	int experience;
	int level;
	string name;
	int dice;

	//Equipped items
	bool leftHand;
	bool rightHand;
	bool head;
	bool torso;
	bool legs;
	bool feet;
};	//end of Unit
#endif
