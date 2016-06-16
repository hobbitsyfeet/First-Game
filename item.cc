
#include "item.h"
//#include "./unit.h"
#include <fstream>
#include <iostream>
using namespace std;

Item::Item(string n , string type, int dam, int def, int val,int dur, bool held){
	itemName=n;
	itemDamage=dam;
	itemType = type;
	itemDefence=def;
	itemWorth=val;
	itemIsEquipped = held;
	itemDurability= dur;
}


string Item::itemGetName(){
	return itemName;
}
string Item::itemGetType(){
	return itemType;
}
int Item::itemGetDamage(){
	return itemDamage;
}
int Item::itemGetDefence(){
	return itemDefence;
}
int Item::itemGetWorth(){
	return itemWorth;
}
int::Item::itemGetDurability(){
  return itemDurability;
}

void Item::viewItem(){
	cout<<itemName<<" ";
	cout<<itemType<<" ";
	if(itemDamage != 0)
		cout<<"DAMAGE:["<<itemDamage<<"] ";
	if(itemDefence != 0)
		cout<<"DEFENCE:["<<itemDefence<<"] ";
	if(itemWorth != 0)
		cout<<"WORTH:["<<itemWorth<<"] ";
	if(itemIsEquipped == true)
		cout<<" [EQUIPPED]";
	cout<<endl;
}
void Item::decrementDurability(){
  itemDurability --;
}
void Item::itemEquip(){
	itemIsEquipped = true;
}

void Item::itemUnequip(){
	itemIsEquipped = false;
}

bool Item::isEquipped(){
return itemIsEquipped;
}


//FileStream
void Item::loadItem(string Name){
	ifstream fin;
	fin.open("item.list");
	fin>>itemName>>itemType>>itemDamage>>itemDefence>>itemWorth>>itemDurability>>itemIsEquipped;

}
//OPERATORS
bool Item::operator == (const Item& i){
	if(itemName == i.itemName)
		return true;
	else 
		return false;
}

Item& Item::operator = (const Item& i){
	itemName = i.itemName;
	itemType = i.itemType;
	itemDamage = i.itemDamage;
	itemDefence = i.itemDefence;
	itemWorth = i.itemWorth;
	itemIsEquipped = i.itemIsEquipped;
	itemDurability = i.itemDurability;
	return *this;
}

//*************
//io functions
//*************
ostream& operator<<(ostream& oStr,const Item& i){
		oStr<<i.itemName<<' ';
		oStr<<i.itemType<<' ';
		oStr<<i.itemDamage<<' ';
		oStr<<i.itemDefence<<' ';
		oStr<<i.itemWorth<<' ';
		oStr<<i.itemIsEquipped<<' ';
return oStr;
}

istream& operator>>(istream& iStr, Item& i){
  iStr >> i.itemName >>i.itemType >>i.itemDamage>>i.itemDefence>>i.itemWorth>>i.itemDurability>>i.itemIsEquipped;
	return iStr;
}



//WEAPONS
