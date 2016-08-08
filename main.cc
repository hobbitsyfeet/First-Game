//*********************
//main
//control for the program
//*********************

//#include "menu.h"
#include "turn.h"
#include "chart.h"
#include <iostream>

using namespace std;

Unit menu();



int main(){
  Chart worlds;
  Turn player;

 // string option;
 // cout<<"what world?>>";
  //cin>>option;
 // worlds.loadWorld(player.getWorld());
 // worlds.displayWorld();
  player.run(worlds);
  //worlds.playWorld();
  //worlds.displayWorld();
return 0;
}
