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

//Functions:Getters
//returns individually values of stats
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

//Function:displayStats
//prints out status of Unit in an in-line order
void Unit::displayStats(){
  cout<<"==============STATS=============="<<endl;
  cout<<setfill(' ');
  cout<<"NAME:"<<name<<endl;
  cout<<"Health:"<<left<<setw(10)<<health<<"Experience:"<<experience<<endl;
  cout<<"Attack:"<<left<<setw(10)<<attack<<"Defence:"<<defence<<endl;
  cout<<setfill('=')<<setw(35)<<"==";
}

//**********COMBAT************

//Function:attackUnit
//passes in another unit and does damage accordingly
void Unit::attackUnit(Unit& target){
  int totalDamage = (this->getAttack()-target.getDefence());
  Item* equipmentUsed;

  //if not dead, attack
  if(target.getHealth() > totalDamage){
    if(inv.searchWeaponEquipped()){
      //getEquipped Weapon
      equipmentUsed = &inv.getItemEquipped();
      //if weapon's durability
      if(equipmentUsed->itemGetDurability() > 0){
      //if the total damage is positive
       if(totalDamage > 0){
          //do damage
          target.health -= totalDamage;
          equipmentUsed->decrementDurability();
          //decrement item's durability
        }
        //no damage inflicted
        else{
         cout<<this->getName()<<" dealt 0 damage to"<< target.getName();
        }
      }
      //the item is broken
      else{
        totalDamage = 1;
        cout<<equipmentUsed->itemGetName()<<" is broken!"<<endl;
        target.health -= totalDamage;
      }
       //show results
       cout<<this->getName()<<" dealt "
	     <<totalDamage
	     <<" damage to "<<target.getName();
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

//Fucntion:distanceUnit
//passes in another unit and returns the distance from current
//using 'distance between two points' equation
int Unit::distanceUnit(const Unit& target){
  int dist;
  //distance between 2 points
  dist = sqrt((target.posX - this->posX) + target.posY - this->posY);
  //because distance cannot be negative
  if(dist< 0)
    return -(dist);
  else 
    return dist;
}

//Function:getPos
//neatly displays  x and y position
void Unit::getPos(){
  cout<<posX<<','<<posY;
}


//***********EQUIPMENT*********

//Function:equipItem
//Searches for an item in inventory
//applies stats to unit and
//applies boolean 'equipped' according to item type
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

//Function:equipItem
//INVERSE OF "equipItem"
//Searches for an item in inventory
//un-applies stats to unit and
//applies boolean 'equipped' according to item type
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

//Function:loadUnit
//INVERSE OF saveUnit
//receives unit information from external FILE
void Unit::loadUnit(string file){
  ifstream fin;
  fin.open("./saves/" + file);
  while(fin.fail()){
    cout<<"invalid player, enter a name>> ";
    cin>>file;
    fin.open("./saves/" + file);
  }
  fin>>name>>level>>health>>stamina>>attack>>defence>>gold>>experience>>dice;
  fin>>leftHandEquipped>>rightHandEquipped>>headEquipped>>torsoEquipped>>legsEquipped>>feetEquipped;
  fin>>posX>>posY;
  fin.close();
  inv.loadInventory(file);
}

//Function:saveUnit
//INVERSE OF loadUnit
//writes unit information to external file
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

//assignment operator for unit
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
//************************************************************************
//************************INVENTORY FUNCTIONS*****************************
//************************************************************************
//************************************************************************

//Function:displayInv
//prints out every item in inventory
void Unit::displayInv(){
  vector<Item>::iterator it;
  cout<<"===============INVENTORY==============="<<endl;
  cout<<"GOLD:"<<gold<<endl;
  for(it=inv.invContainer.begin(); it< inv.invContainer.end(); it++){
    cout<<"- ";
    it->viewItem();
  }
  cout<<"=======================================";
}

//NOT DONE
void Unit::inventory::pickUp(Item a){
  invContainer.push_back(a);
}
//NOT DONE
void Unit::inventory::dropItem(Item a){
   a.itemUnequip();
}

//***********FILE************
//Function: saveInventory
//similar to save Unit
//prints unit's inventory to file
void Unit::inventory::saveInventory(string unitName){
  vector<Item>::iterator it;
  ofstream fout;
  //open file at destination
  fout.open("./saves/" + unitName +"Inv");
  for(it=invContainer.begin(); it< invContainer.end(); it++){
    if(it+1 != invContainer.end())
      fout<<*it<<endl;
    else
      fout<<*it;
  }
  fout.close();
}

//Function:loadInventory
//Gets stats individually from file
//creates an item with those stats
//pushes it into Unit's inventory
void Unit::inventory::loadInventory(string unitName){
  
  //assigns default stats for if inventory is empty or new
  string iName = "Pebble";
  string iType = "Right-Hand";
  int dam = 1;
  int def = 0;
  int val = 1;
  int dur = 20;
  bool eq = 0;
  
  ifstream fin;
  fin.open("./saves/" + unitName +"Inv");
  
  //for each item in file get stats and overwrite old ones
  while(!fin.eof()){
    fin>>iName>>iType>>dam>>def>>val>>dur>>eq;
    //create temp item with stats
    Item temp(iName, iType, dam, def,val,dur,eq);
    //push into inventory
    pickUp(temp);
  }
  fin.close();
}


bool Unit::inventory::searchWeaponEquipped(){
  vector<Item>::iterator it;

  for(it=invContainer.begin(); it< invContainer.end(); it++){
    if(it->itemGetType() == "Right-Hand" && it->itemGetEquipped() == true){
      return true;
    }
    else if(it->itemGetType() == "Left-Hand" && it->itemGetEquipped() == true){
       return true;
    }
    else if(it->itemGetType() == "Two-Hands" && it->itemGetEquipped() == true){
        return true;
    }
  }
  return false;
}

Item Unit::inventory::getSearch(Item iSearch){
  vector<Item>::iterator it;
  for(it=invContainer.begin(); it< invContainer.end(); it++){
    if (*it == iSearch)
      return *it;
  }
  return *it;
  cout<<"test";
}

Item& Unit::inventory::getItemEquipped(){
    vector<Item>::iterator it;
    for(it=invContainer.begin(); it< invContainer.end(); it++){
      if(it->itemGetType() == "Right-Hand" && it->itemGetEquipped() == true){
        return *it;
    }
     else if(it->itemGetType() == "Left-Hand" && it->itemGetEquipped() == true){
      return *it;
     }
      else if(it->itemGetType() == "Two-Hands" && it->itemGetEquipped() == true){
      return *it;
    }
  }
}

