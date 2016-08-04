#include "turn.h"
#include "unit.h"
#include "chart.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Turn::run(Chart& world){
  string option;
	string pname;
  int x,y;
  //load info
  getPlayer();
  //world.searchFor('O',player.posX,player.posY);
  cout<<"Loaded:"<<player.getName();
	pname = player.getName();

  //start commands
//worlds.loadWorld(option);

  while(option != "end"){

		//First input
    cout<<endl<<">>";
    cin>>option;


      //**INVENTORY**
    if(option == "inv"){
      player.displayInv();
    }
    //**STATS**
    else if (option == "stats"){
      player.displayStats();
    }
    //**MOVE**
    else if(option == "move"){
			int dist;
			cout<<"which way>>";
			cin>>option;
			cout<<"how much>>";

			cin>>dist;
			if(option == "north" || option == "up"){
				//if(world.canEnter( player.getPosX(), (player.getPosY()+dist) ) )
				player.posY += dist;
			}

			else if(option == "east" || option == "right"){
				//if(world.canEnter( (player.getPosX()+dist), player.getPosY() ) )
				player.posX += dist;
			}

			else if(option == "south" || option == "down"){
				//if(world.canEnter(player.getPosX(), (player.getPosY()-dist) ) )
				player.posY -= dist;
			}

			else if(option == "west" || option == "left"){
				//if(world.canEnter( (player.getPosX()-dist), player.getPosY() ) )
				player.posX -= dist;
			}
			world.displayRange(player.getPosX(),player.getPosY(),5);
		}


		else if(option == "map"){
			//world.displayWorld();
			//cout<<endl;
			world.displayRange(player.getPosX(),player.getPosY(),5);
			player.getPos();
		}
		else if(option == "pos"){
			player.getPos();
		}
		else if(option == "target-pos"){
			target.getPos();
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
		else if(option == "attack"){
			player.attackUnit(target);
		}
		else if(option =="loot"){
			if(target.getHealth() == 0){
				target.displayInv();
				cout<<endl<<"choose an item";
				cin>>option;
				if(option!="nothing")
				player.lootUnit(option,target);
				if(target.getName() != "NoName")
				target.saveUnit(target.getName());
				player.saveUnit(pname);
			}
			else cout<<"Cannot loot";
		}
		else if(option == "give"){
			player.displayInv();
			cout<<endl<<"what to give>>";
			cin>>option;
      if(option != "nothing")
			target.lootUnit(option,player);
			if(target.getName() != "NoName")
			target.saveUnit(target.getName());
			player.saveUnit(pname);
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
		//if you end up attacking yourself, stats wouldn't differ from saved info.
		//player.loadUnit(player.getName());
		else if(option =="save"){
			cout<<"who >>";
			cin>>option;
			player.saveUnit(option);
		}

		else if(option == "help" || option =="?"){
			cout<<"Command List: \n";
			cout<<"Actions,Stats or Other >>";
			cin>>option;
			if(option =="actions"){
				cout<<"Actions:"<<endl
				<<"attack: Deals damage to target"<<endl
				<<"equip: Equips item and gain stats"<<endl
				<<"un-equip: Un-equip item in order to equip another"<<endl
				<<"move: North,east,south,west for a distance"<<endl
				<<"give: give another target an item from your inventory"<<endl
				<<"loot: Put dead target's item into your inventory"<<endl
				<<"taret: Name a unit to target, get info and attack"<<endl
				<<"t-bag: Tbag your target!"<<endl;
			}
		}
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
