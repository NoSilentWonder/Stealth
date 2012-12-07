#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sprites.h"

//PLAYER CLASS INHERITED FROM WINSPRITES
//THIS CLASS CREATES A PLAYER SPRITE WHICH IS CONTROLLED BY THE PLAYER USING THE KEYBOARD KEYS
//W, S, A and D and SPACEBAR TO USE THROWING STARS.
//IT HAS A COLOURED "EYE" ON ONE EDGE INDICATING DIRECTION IT IS FACING AND ALSO THE HEALTH
//OF THE PLAYER BASED ON THE EYE COLOUR - GREEN, YELLOW, ORANGE, RED.
class Player: public WinSprite 
{
public:
	Player(void); //constructor that positions the player at 0, 0
	
	void Control(bool k[256]); //takes in values from keyboard and moves/rotates player accordingly
	
	bool HitEnemy(WinSprite E); //collision detection check between given enemy sprite and active Star sprite
	
	void Shot(void); //descreases player health after enemy shoots them
	
	bool HasKey(void); //returns the key boolean
	
	void PickUpKey(void); //sets key boolean to true - called when player collides with key object
	
	bool GameWon(void); //checks player position in grid - if outside maze area, player has gone through exit and completed the level
	
	bool GameLost(void); //returns dead boolean
	
	void Update(void); //updates player health display, position and position of throwing star if active
	
	void Reset(void); //resets player variables to defaults and moves off screen

	WinSprite Star; //Star sprite

private:
	void LoadBitMapsandMasks(void); //stores all bitmaps for player animations and masks

	void HealthDisplay(void); //controls colour of player eye based on health
	
	void Death(void); //set dead boolean to true and changes player colouring

	HBITMAP LoadABitmap(LPSTR szFileName); //returns a BITMAP of the provided .bmp file (Matthew Bett's function)

	HBITMAP animations[13];

	int clr; //checks which colour eyes should be so that correct animation bitmap is used

	int steps; //toggles between walking animation bitmaps

	HBITMAP masks[4];

	int health; //player health
	int throw_time; //timer for throwing stars
	bool key; //boolean for holding a key
	bool dead; //is player still alive
};


#endif