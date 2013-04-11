#include "MapEditor.h"
#include "Camera.h"
#include <iostream>
using namespace std;

// initialize static variables
string MapEditor::filenameSave[4];
string MapEditor::filenameLoad[4];
vector<Enemy*> MapEditor::EnemyList;
bool MapEditor::runLoadMaps=false;
// tile order: deepwater,water,sand,grass,grass,evergreen,tree,grass,grass,dirt,rock,snow,mountains,snow,rock,lava
int MapEditor::tileX[] = {0,6,3,0,0,6,0,0,0,0,3,3,6,3,3,6};
int MapEditor::tileY[] = {2,1,1,1,1,6,6,1,1,3,0,9,9,9,0,8};
int MapEditor::tileTypes[] = {2,2,1,1,1,2,2,1,1,1,1,1,2,1,1,2}; // 1 = traversable, 2 = non-traversable

MapEditor::MapEditor(string inputarg) {
	// Initialize the surfaces to NULL to avoid errors
	Surf_Display = NULL;
	Control_Display = NULL;
	Tileset = NULL;
	Selector =  NULL;
	Objective=NULL;
	Menu = NULL;
		dispMenu = false;
	HeartBar = NULL;
	TitleScreen = NULL;
		dispTitle = true;

	Player_Character = NULL;
	
	// Initialize Font objects to NULL
	TTF_Font *XObjectiveFont = NULL;

	currentTileXID=0;
	currentTileYID=1;

	Running = true;
	Quit = false;

	if(inputarg=="debug"){
	  debug=true;
	  cout<<"DEBUG MODE"<<endl;
	}
	else debug=false;
}

int MapEditor::OnExecute() {
  srand(time(NULL));

  Camera::CameraControl.ChangeMapView();

	// Initialize the game; if it fails, return error code and close program
	if(OnInit() == false){
		return -1;
	}

	SDL_Event Event;

	while(Running){
		// check for events (user input), pass one at a time to OnEvent(
		while(SDL_PollEvent(&Event)){
			OnEvent(&Event);
		}
		
		// Manipulate data
		OnLoop();

	  // switch map view if necessary
	  if(runLoadMaps==true){
	    LoadMaps(); // HAVING ERRORS
	    runLoadMaps=false;
	  }
		// Render the output
		OnRender();
	}

	OnSave(); // doesn't actually do anything anymore... might later, though, if we actually save stuff

	GameOver();

	// Clean up trash
	OnCleanup();

	return 0;
}

bool MapEditor::LoadMaps(){
  for(int i=0;i<4;i++){
    if(gameMap[i].OnLoad("/maps/1.map",filenameLoad[i],currentTileXID,currentTileYID) == false) {
      cout<<"  Error loading "<<filenameLoad[i]<<endl;
      return false;
    }
  }
  return true;
}

void MapEditor::GameOver(){
  SDL_Event Event;
  while(!Quit){
    while(SDL_PollEvent(&Event)) OnEvent(&Event);
  }
}

int main(int argc, char* argv[]) {
  string arg;
  if(argc>1) arg=argv[1];
  else arg="";

  MapEditor theApp(arg);
  return theApp.OnExecute();
}
