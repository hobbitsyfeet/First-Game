#ifndef TURN_H
#define TURN_H

#include "unit.h"
#include "chart.h"
//#include "item.h"

class Turn{
	//friend class Chart;
 public:
  void run(Chart&);
 private:
	void attackTarget();
	Unit getPlayer();
 	Unit player;
  	Unit target;
};


#endif
