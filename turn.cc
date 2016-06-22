#include "turn.h"
#include "unit.h"
#include "chart.h"
#include <iostream>
using namespace std;

void Turn::run(Chart& world){
  string option;
  int x,y;
  //load info
  getPlayer();
  world.searchFor('O',player.posX,player.posY);
  cout<<"Loaded:"<<player.getName();

  //start commands
//worlds.loadWorld(option); 

  while(option != "end"){

    cout<<">>";
    cin>>option;
      
    if(option == "inv"){
      player.displayInv();
    }
    else if (option == "stats"){
      player.displayStats();
    }

    else if(option == "move"){
      cout<<"which way>>";
      cin>>option;

      if(option == "north" || option == "up"){
        if(world.canEnter( player.getPosX(), (player.getPosY()+1) ) )
          player.posY += 1;
      }

      else if(option == "east" || option == "right"){
         if(world.canEnter( (player.getPosX()+1), player.getPosY() ) )
           player.posX += 1;
      }

      else if(option == "south" || option == "down"){
        if(world.canEnter(player.getPosX(), (player.getPosY()-1) ) )
          player.posY -= 1;
      }

      else if(option == "west" || option == "left"){
        if(world.canEnter( (player.getPosX()-1), player.getPosY() ) )
           player.posX -= 1;
      }

    }

    else if(option == "help" || option =="?"){
      cout<<"commands:"<<endl<<"inv, end,equip, un-equip, stats, move,"<<endl
	  <<"";
    }
    else if(option == "map"){
      player.getPos();
      world.displayWorld();
    }
    else if(option == "equip"){
      cout<<"What do you want to equip? >>";
      cin>>option;
      player.equipItem(option);
    }
    else if(option == "un-equip"){
      cout<<"What do you want to un-equip? >>";
      cin>>option;
      player.unEquipItem(option);
    }
    else if(option == "target"){
      cout<<"Who >>";
      cin >> option;
        target.loadUnit(option);
        cout<<"targeted:"<<endl;
        target.displayStats();
    }
    else if (option == "target-stats"){
       target.displayStats();
    }
    else if(option == "move" || option == "walk"){

    }
    else if(option == "attack"){
      player.attackUnit(target);
    }
    else if (option == "distance"){
      cout<<player.distanceTo(target.getPosX(),target.getPosY());
    }
    else if (option == "tbag"){
      cout<<"how many times?>>";
      int tbags;
      cin>>tbags;
      //static_cast<int>option;
      for(int i =1;i<=tbags; i++){
      cout<<player.getName()<<" T-bagged ";

      if(target.getName() == player.getName())
        cout<<"himself ";
      else
      cout<<target.getName()<<" ";

      cout<<i;
      if(i<=1)
        cout<<" time"<<endl;
      else
          cout<<" times"<<endl;
      }
    }
    player.saveUnit(player.getName());
    target.saveUnit(target.getName());
    //if you end up attacking yourself, stats wouldn't differ from saved info.
    //player.loadUnit(player.getName());
  }
}

Unit Turn::getPlayer(){
  string option="";
  //if(player.getName() == "NoName"){
 // do{
   cout<<"new or load>>"<<endl;
   cin>>option;
  //}while(option !=);
    if(option == "new"){
      cout<<"who? >>";
      cin>> option;
      player.saveUnit(option);
      player.loadUnit(option); 
    }
    else if(option == "load"){
      cout<<"who? >>";
      cin >> option;
      player.loadUnit(option);
    }

  return player;
}
