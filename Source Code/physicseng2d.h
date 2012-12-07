#ifndef _PHYSICSENG2D_H_
#define _PHYSICSENG2D_H_

#include "player.h"
#include "enemy.h"

//2D PHYSICS ENGINE FUNCTIONS CONTAINED IN A NAMESPACE PHYSICSENG
//FUNCTIONS TO DETECT VARIOUS COLLISIONS AND HANDLE REACTIONS TO THOSE COLLISIONS
namespace PhysicsEng 
{
	//Collision detection algorithms
	bool HitBox(WinSprite &S1, WinSprite &S2); //collisions using bounding boxes
	
	bool HitCircle(WinSprite &S1, WinSprite &S2); //radial collisions
	
	void HitWall(WinSprite &Spr); //collisions against edge of screen - currently includes NoGo reaction call
	
	int LineOfSight(Enemy &E, Player &P); //Line of Sight detection for enemies - checks angle and distance of player from enemy
	
	bool CheckGridSpaces(Enemy &E, Player &P); //check grid squares between enemy and to find out if they are blocked
	
	bool IsLoSClear(Enemy &E, Player &P, WinSprite W); //checks to see if enemy LoS to player blocked by a wall
	
	//Collision reaction algorithms
	void NoGo(WinSprite &S); //returns sprite to position immediately prior to collision
	
	void UnlockDoor(WinSprite & door); //animation on door when unlocked (called due player collision while holding key)

}

#endif