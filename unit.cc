
#include "unit.h"
#include "item.h"
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
//default constructor
Unit::Unit(string Name,int Level, int Health,int Attack,int Defence, int Exp, int Gold, int Stam, int Dice, int xpos, int ypos){
  name=Name;
  level = Level;
  health=Health;
  attack=Attack;
  defence=Defence;
  gold=Gold;
  experience=Exp;
  stamina = Stam;
  dice = Dice;

  posX = xpos;
  posY = ypos;

}

//*******STATS*********
void Unit::displayStats(){
  cout<<"==============STATS=============="<<endl;
  cout<<setfill(' ');
  cout<<"NAME:"<<name<<endl;
  cout<<"Health:"<<left<<setw(10)<<health<<"Experience:"<<experience<<endl;
  cout<<"Attack:"<<left<<setw(10)<<attack<<"Defence:"<<defence<<endl;
  cout<<setfill('=')<<setw(35)<<"==";
}
string Unit::getName()const{
  return name;
}
int Unit::getLevel()const{
	return level;
}
int Unit::getHealth()const{
  return health;
}
int Unit::getStamina()const{
  return stamina;
}
int Unit::getAttack()const{
  return attack;//add to item damage
}
int Unit::getDefence()const{
  return defence;
}
int Unit::getGold()const{
  return gold;
}
int Unit::getExp()const{
  return experience;
}
int Unit::getPosY(){
	return posY;
}
int Unit:: getPosX(){
	return posX;
}
//**********COMBAT************
void Unit::attackUnit(Unit& target){
	int totalDamage = (this->getAttack()-target.getDefence());
	//if not dead, attack
	if(target.getHealth() > totalDamage){
		//damage inflicted
		if(totalDamage > 0){
			target.health -= totalDamage;
			cout<<this->getName()<<" dealt "
				<<totalDamage
				<<" damage to "<<target.getName();
		}
		//no damage inflicted
		else{
			cout<<this->getName()<<" dealt 0 damage to"<< target.getName();
		}
			//save b/c stat change
			target.saveUnit("/enemies/"+target.getName());
	}
	//they are dead, announce and do no action
	else{
		target.health = 0;
		cout<<target.getName()<<" is dead"<<endl;
	}

}

int Unit::distanceUnit(const Unit& target){
	int dist;
	//distance between 2 points
	dist = sqrt((target.posX - this->posX) + target.posY - this->posY);
	if(dist< 0)
		return -(dist);
	else 
		return dist;
}

void Unit::getPos(){
	cout<<posX<<','<<posY<<endl;
}


//***********EQUIPMENT*********
void Unit::equipItem(string i){

	vector<Item>::iterator it;
	bool didEquip=false;
	for(it=inv.invContainer.begin(); it< inv.invContainer.end() || it->itemGetName() == i; it++){

		if(it->itemGetName() == i){
			if(it->itemGetType() == "Right-Hand" && rightHandEquipped == false){
				rightHandEquipped = true;
				didEquip = true;
			}
			else if(it->itemGetType() == "Left-Hand" && leftHandEquipped == false){
				leftHandEquipped = true;
				didEquip = true;
			}
			else if(it->itemGetType() == "Two-Hands" && leftHandEquipped == false && rightHandEquipped == false ){
				leftHandEquipped = true;
				rightHandEquipped = true;
				didEquip = true;
			}
			else if(it->itemGetType() == "Helmet" && headEquipped == false){
				headEquipped = true;
				didEquip = true;
			}
			else if(it->itemGetType() == "Body-Armour" && torsoEquipped == false){
				torsoEquipped = true;
				didEquip = true;
			}
			else if(it->itemGetType() == "Leggings" && legsEquipped == false){
				legsEquipped = true;
				didEquip = true;
			}
			else if(it->itemGetType() == "Boots" && feetEquipped == false){
				feetEquipped = true;
				didEquip = true;
			}

			if(didEquip == true){
				cout<<i<<" equipped"<<endl;
				attack += it->itemGetDamage();
				defence += it->itemGetDefence();
				it->itemEquip();
			}
		}
	}
}

void Unit::unEquipItem(string i){
	vector<Item>::iterator it;
	bool didEquip = false;
	for(it=inv.invContainer.begin(); it< inv.invContainer.end() || it->itemGetName() == i; it++){
		if(it->itemGetName() == i){
			if(it->itemGetType() == "Right-Hand" && rightHandEquipped == true){
	      rightHandEquipped = false;
	      didEquip = true;
	    }
	    else if(it->itemGetType() == "Left-Hand" && rightHandEquipped == true){
	      rightHandEquipped = false;
	      didEquip = true;
	    }
	    else if(it->itemGetType() == "Two-Hands" && rightHandEquipped == true && leftHandEquipped == true){
	      rightHandEquipped = false;
	      leftHandEquipped = false;
	      didEquip = true;
	    }
	    else if(it->itemGetType() == "Helmet" && headEquipped == true){
	      headEquipped = false;
	      didEquip = true;
	    }
	    else if(it->itemGetType() == "Body-Armour" && torsoEquipped == true){
	      torsoEquipped = false;
	      didEquip = true;
	    }
	    else if(it->itemGetType() == "Leggings" && legsEquipped == true){
	      legsEquipped = false;
	      didEquip = true;
	    }
	    else if(it->itemGetType() == "Boots" && feetEquipped == true){
	      feetEquipped = false;
	      didEquip = true;
	    }
			if(didEquip == true){
				cout<<i<<" un-equipped"<<endl;
				attack -= it->itemGetDamage();
				defence -= it->itemGetDefence();
				it->itemUnequip();
			}
			else
				cout<<"Could not un-equip "<<i<<endl;
	  }
	}
}

//***********FILE************
void Unit::loadUnit(string file){
  ifstream fin;
	fin.open("./saves/" + file);
	fin>>name>>level>>health>>stamina>>attack>>defence>>gold>>experience>>dice;
	fin>>leftHandEquipped>>rightHandEquipped>>headEquipped>>torsoEquipped>>legsEquipped>>feetEquipped;
	fin>>posX>>posY;
	fin.close();
	inv.loadInventory(file);
}

void Unit::saveUnit(string file){
	ofstream fout;
	fout.open("./saves/" + file);
	fout<<file<<' '<<level<<' '<<health<<' '<<stamina<<' '<<attack<<' '<<defence<<' '<<gold<<' '<<experience<<' '<<dice<<' ';
	fout<<leftHandEquipped<<' '<<rightHandEquipped<<' '<<headEquipped<<' '<<torsoEquipped<<' '<<legsEquipped<<' '<<feetEquipped<<' ';
	fout<<posX<<' '<<posY<<' ';
	fout.close();
	inv.saveInventory(file);
}


//***************OPERATORS*******************
Unit& Unit::operator = (const Unit& i){
	name = i.name;
	health = i.health;
	stamina = i.stamina;
	attack = i.attack;
	defence = i.defence;
	gold = i.gold;
	experience = i.experience;
	return *this;
}


//************************************************************************
//************************INVENTORY FUNCTIONS*****************************
//************************************************************************



void Unit::inventory::pickUp(Item a){
	invContainer.push_back(a);
}

void Unit::inventory::dropItem(Item a){
	a.itemUnequip();
}

Item Unit::inventory::findItem(string a){
  Item temp;
  vector<Item>::iterator it;
  for(it=invContainer.begin(); it< invContainer.end();it++){
    if(it->itemGetName()==a)
      return temp;
  }
  return temp;
}

void Unit::displayInv(){
	vector<Item>::iterator it;

	cout<<endl;
cout<<"===============INVENTORY==============="<<endl;
cout<<"GOLD:"<<gold<<endl;
	for(it=inv.invContainer.begin(); it< inv.invContainer.end(); it++){
		cout<<"- ";
		it->viewItem();
	}
cout<<"=======================================";
}

void Unit::inventory::saveInventory(string unitName){
	vector<Item>::iterator it;
	ofstream fout;
	fout.open("./saves/" + unitName +"Inv");
	for(it=invContainer.begin(); it< invContainer.end(); it++){
		if(it+1 != invContainer.end())
			fout<<*it<<endl;
		else
			fout<<*it;
	}
	fout.close();
}

void Unit::inventory::loadInventory(string unitName){
	string iName = "Pebble";
	string iType = "Right-Hand";
	int dam = 1;
	int def = 0;
	int val = 1;
	int dur = 20;
	bool eq = 0;
	
	ifstream fin;
	fin.open("./saves/" + unitName +"Inv");
	
	while(!fin.eof()){
	  fin>>iName>>iType>>dam>>def>>val>>dur>>eq;
	  Item temp(iName, iType, dam, def,val,dur,eq);
		pickUp(temp);
	}
	fin.close();
}

