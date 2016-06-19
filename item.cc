
#include "item.h"
#include <fstream>
#include <iostream>
using namespace std;

//default constructor
Item::Item(string n , string type, int dam, int def, int val,int dur, bool held){
	itemName=n;
	itemDamage=dam;
	itemType = type;
	itemDefence=def;
	itemWorth=val;
	itemIsEquipped = held;
	itemDurability= dur;
}

//*******STATS*********
//Functions:Getters
//returns individually values of stats
string Item::itemGetName()const{
	return itemName;
}
string Item::itemGetType()const{
	return itemType;
}
int Item::itemGetDamage()const{
	return itemDamage;
}
int Item::itemGetDefence()const{
	return itemDefence;
}
int Item::itemGetWorth()const{
	return itemWorth;
}
int::Item::itemGetDurability() const{
  return itemDurability;
}
bool Item::isEquipped(){
return itemIsEquipped;
}

//Function:displayStats
//prints out status of Unit in an in-line order
void Item::viewItem(){
	cout<<itemName<<" ";
	cout<<itemType<<" ";
	if(itemDamage != 0)
		cout<<"DAMAGE:["<<itemDamage<<"] ";
	if(itemDefence != 0)
		cout<<"DEFENCE:["<<itemDefence<<"] ";
	if(itemWorth != 0)
		cout<<"WORTH:["<<itemWorth<<"] ";
	cout<<itemDurability;
	if(itemIsEquipped == true)
		cout<<" [EQUIPPED]";
	cout<<endl;
}

//**********Modifiers***********
void Item::decrementDurability(){
  itemDurability --;
}
void Item::itemEquip(){
	itemIsEquipped = true;
}
void Item::itemUnequip(){
	itemIsEquipped = false;
}



//***********FILE************
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
