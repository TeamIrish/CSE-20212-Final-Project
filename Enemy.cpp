// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

#include "MapEditor.h"
#include <cstdlib>

using namespace std;

// macros for entityStateX (direction)
const int ENEMY_DOWN = 0;
const int ENEMY_UP = 1;
const int ENEMY_RIGHT = 2;
const int ENEMY_LEFT = 3;

// number of frames in the enemy's animation cycle
const int NUM_FRAMES = 4;

Enemy::Enemy( string file, int w, int h, int x, int y, int s )
	: Entity( file, w, h, x, y, s )
{ }

// randomly select enemy's next move, biased towards current direction
void Enemy::OnLoop()
{
	// random number to determine enemy's direction
	int randNum = rand() % 30;

	// move and set next state depending on current state
	switch( entityStateX )
	{
		case ENEMY_DOWN:
			Y += width / 4; // move

			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) Y -= width / 4; // undo the move
			// set next state pseudo-randomly
			if( randNum < 27 ) entityStateX = ENEMY_DOWN;
			else if( randNum == 27 ) entityStateX = ENEMY_RIGHT;
			else if( randNum == 28 ) entityStateX = ENEMY_UP;
			else if( randNum == 29 ) entityStateX = ENEMY_LEFT;
			break;

		case ENEMY_RIGHT:
			X += width / 4; // move

			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) X -= width / 4; // undo the move
			// set next state pseudo-randomly
			if( randNum < 27 ) entityStateX = ENEMY_RIGHT;
			else if( randNum == 27 ) entityStateX = ENEMY_DOWN;
			else if( randNum == 28 ) entityStateX = ENEMY_LEFT;
			else if( randNum == 29 ) entityStateX = ENEMY_UP;
			break;

		case ENEMY_UP:
			Y -= width / 4; // move

			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) Y += width / 4; // undo the move
			// set next state pseudo-randomly
			if( randNum < 27 ) entityStateX = ENEMY_UP;
			else if( randNum == 27 ) entityStateX = ENEMY_LEFT;
			else if( randNum == 28 ) entityStateX = ENEMY_RIGHT;
			else if( randNum == 29 ) entityStateX = ENEMY_DOWN;
			break;

		case ENEMY_LEFT:
			X -= width / 4; // move

			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) X += width / 4; // undo the move
			// set next state pseudo-randomly
			if( randNum < 27 ) entityStateX = ENEMY_LEFT;
			else if( randNum == 27 ) entityStateX = ENEMY_RIGHT;
			else if( randNum == 28 ) entityStateX = ENEMY_UP;
			else if( randNum == 29 ) entityStateX = ENEMY_DOWN;
			break;
	}

	// make sure the enemy is in bounds
	if( X < width/2 ) { // too far left
		X = width/2;
	}
	if( (X + width/2) > (2 * MAP_WIDTH * TILE_SIZE) ) { // too far right
		X = 2 * MAP_WIDTH * TILE_SIZE - width/2;
	}
	if( Y < height/2 ) { // too far up
		Y = height/2;
	}
	if( (Y + height) > (2 * MAP_HEIGHT * TILE_SIZE) ) { // too far down
		Y = 2* MAP_HEIGHT * TILE_SIZE - height;
	}

	// shift animation frame
	if( entityStateY < NUM_FRAMES - 1 ) entityStateY++;
	else entityStateY = 0;
}
