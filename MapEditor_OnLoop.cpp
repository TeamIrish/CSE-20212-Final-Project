#include "MapEditor.h"
 
void MapEditor::OnLoop() {
	// Move camera
	int moveSize = 5;
	if(Camera::CameraControl.MovingLeft == true){
		Camera::CameraControl.OnMove(moveSize,0);
		if(CheckCollision()) Camera::CameraControl.OnMove(-moveSize,0);
	}
	if(Camera::CameraControl.MovingRight == true){
		Camera::CameraControl.OnMove(-moveSize,0);
		if(CheckCollision()) Camera::CameraControl.OnMove(moveSize,0);
	}
	if(Camera::CameraControl.MovingUp == true){
		Camera::CameraControl.OnMove(0,moveSize);
		if(CheckCollision()) Camera::CameraControl.OnMove(0,-moveSize);
	}
	if(Camera::CameraControl.MovingDown == true){
		Camera::CameraControl.OnMove(0,-moveSize);
		if(CheckCollision()) Camera::CameraControl.OnMove(0,moveSize);
	}

	// Check to make sure that the camera didn't move out of bounds - if so, change map view
	Camera::CameraControl.CheckBounds();

	// Change player character state
	Camera::CameraControl.AnimateCharacter();

	// Check for collision with enemies
	if(CheckEnemyCollisions()) Running=false;

	// Decide whether to spawn enemy
	if(rand()%100<1 && EnemyList.size()<6) SpawnEnemy();
}


bool MapEditor::CheckCollision(){
  int X,Y,ID;
  X = -(Camera::CameraControl.GetX() - WWIDTH/2) / TILE_SIZE;
  Y = -(Camera::CameraControl.GetY() - WHEIGHT/2) / TILE_SIZE;

	int mapID = 0;
	if(X > MAP_WIDTH){
		X = X - MAP_WIDTH;
		mapID += 1;
	}
	if(Y > MAP_HEIGHT){
		Y = Y - MAP_HEIGHT;
		mapID += 2;
	}

	//cout<<"Tile "<<X<<","<<Y<<": "<<"(mapID = "<<mapID<<"): ";
  ID = Y*MAP_WIDTH + X;

	if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_TRAVERSABLE){
		//cout<<"Traversable"<<endl;
		return false;
	}else if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_NON_TRAVERSABLE){
		//cout<<"Non-traversable"<<endl;
		return true;
	}else{
		//cout<<"Other."<<endl;
		return false;
	}
}


void MapEditor::SpawnEnemy(){
  string typestring = "golem.png";
  // generate random coordinates onscreen
  int spawnX = -Camera::CameraControl.GetX()+WWIDTH/2+pow(-1,rand()%2)*(rand()%(WWIDTH/3));
  int spawnY = -Camera::CameraControl.GetY()+WHEIGHT/2+pow(-1,rand()%2)*(rand()%(WHEIGHT/3));
  // move coordinates to somewhere offscreen
  int random=rand()%3;
  if(random>0) spawnX += pow(-1,rand()%2)*WWIDTH;
  if(random<2) spawnY += pow(-1,rand()%2)*WHEIGHT;

  // instantiate enemy and add to list
  Enemy* tmp = new Enemy(typestring,32,32,spawnX,spawnY);
  EnemyList.push_back(tmp);
  cout<<"Enemy Spawned: "<<spawnX/TILE_SIZE<<","<<spawnY/TILE_SIZE<<endl;
}

bool MapEditor::CheckEnemyCollisions(){
  int charX = -Camera::CameraControl.GetX()+WWIDTH/2;
  int charY = -Camera::CameraControl.GetY()+WHEIGHT/2;

  for(int i=0;i<EnemyList.size();i++){
    int Xdist = (CHARACTER_W + EnemyList[i]->getW())/2;
    int Ydist = (CHARACTER_H + EnemyList[i]->getH())/2;
    if(abs(charX-EnemyList[i]->getX())<Xdist && abs(charY-EnemyList[i]->getY())<Ydist) return true;
  }
  return false;
}
