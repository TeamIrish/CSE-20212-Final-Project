#ifndef HEART_H_
	#define HEART_H_

#include "MapEditor.h"
#include "Entity.h"

class Heart : public Entity {
 public:
  Heart(int,int);
  void OnLoop();
};

#endif