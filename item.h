#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using namespace std;

class Item{
public:
  Item(string="unknown", string ="Right-Hand",int=0,int=0,int=0,int=20,bool= false);


  //modifiers
  void decrementDurability();
	//GETTERS
	string itemGetName()const;
	string itemGetType()const;
	int itemGetDamage()const;
	int itemGetDefence()const;
	int itemGetWorth()const;
	int itemGetDurability()const;
	
	//printing and IOstream
	void loadItem(string);
	void viewItem();


	//statuses
	void itemEquip();
	void itemUnequip();
	bool isEquipped();


	//operators
	bool operator == (const Item&);
	Item& operator = (const Item&);

	//friends
	friend ostream& operator << (ostream&, const Item&);
	friend istream& operator >> (istream&, Item&);

private:
	//variables
	string itemName;
	string itemType;
	int itemDamage;
	int itemDefence;
	int itemWorth;
	int itemDurability;
	bool itemIsEquipped;
	
};
#endif
