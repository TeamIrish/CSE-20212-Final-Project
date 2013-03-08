#include "MapEditor.h"
#include "Camera.h"
#include <iostream>
using namespace std;

// initialize static variables
string MapEditor::filenameSave[4];
string MapEditor::filenameLoad[4];
MapEditor MapEditor::MapEditorControl;
bool MapEditor::runLoadMaps=false;
// tile order: lava,rock,snow,mountains,snow,rock,dirt,grass,grass,tree,evergreen,grass,grass,sand,water,deepwater
int MapEditor::tileX[] = {6,3,3,6,3,3,0,0,0,0,6,0,0,3,6,0};
int MapEditor::tileY[] = {8,0,9,9,9,0,3,1,1,6,6,1,1,1,1,2};

MapEditor::MapEditor() {
        srand(time(NULL));
	// Initialize the surfaces to NULL to avoid errors
	Surf_Display = NULL;
	Control_Display = NULL;
	Tileset = NULL;
	Selector =  NULL;

	currentTileXID=0;
	currentTileYID=1;

	Load = false;
	Running = true;
}

void MapEditor::UserInput(){
  /*char input;

	cout << "Would you like to load a file? [y/n] ";
	cin >> input;
	if(input=='y' || input == 'Y'){
		Load = true;
	}
	if(input=='n' || input == 'N'){

	}

	if(Load == true){
	  cout << "Which file would you like to load?";
	  cin >> filenameLoad;
	  filenameLoad = "maps/"+filenameLoad;  // loads from maps directory
	  cout << "What filename would you like to save this under? ";
	  cin >> filenameSave;
	  filenameSave = "maps/"+filenameSave;  // saves to maps directory
	}else{
	  cout << "What filename would you like to save this under? ";
	  cin >> filenameSave;
	  filenameLoad = filenameSave = "maps/"+filenameSave;  // puts file in maps directory
	  RandomMapGenerate(filenameSave);
	  Load = true;
	  }*/
}

int MapEditor::OnExecute() {
  //UserInput();
  Load=true;
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
	    LoadMaps();
	    runLoadMaps=false;
	  }
		// Render the output
		OnRender();
	}

	OnSave();

	// Clean up trash
	OnCleanup();

	return 0;
}

bool MapEditor::LoadMaps(){
  for(int i=0;i<4;i++){
    if(gameMap[i].OnLoad("/maps/1.map",Load,filenameLoad[i],currentTileXID,currentTileYID) == false) {
      cout<<"  Error loading "<<filenameLoad[i]<<endl;
    }
  }
}

int main(int argc, char* argv[]) {

    MapEditor theApp;
    return theApp.OnExecute();
}
