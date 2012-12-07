#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "sprites.h"
#include "pathfinder.h"

//ENEMY CLASS INHERITED FROM WINSPRITES
//THIS CLASS CREATES ENEMY SPRITES WHICH PATROL BETWEEN TWO GIVEN POINTS USING 
//AN A* PATHFINDING ALGORITHM. THEY WILL AlSO SHOOT AT THE PLAYER IF HE MOVES IN
//THEIR LINE OF SIGHT.
//THE ENEMIES HAVE A COLOURED "EYE" INDICATING THE DIRECTION THEY ARE FACING AND 
//THEIR ALERT STATUS - GREEN FOR NORMAL, RED FOR ALERTED.
class Enemy: public WinSprite 
{

public:
	//PROTOTYPES///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Enemy(void); //default constructor

	void SetPatrol(int a1, int b1, int a2, int b2, int t); //sets a start and end grid square for patrol route and wait timer
	
	void Chase(WinSprite p); //player spotted - enemy turns to face player and will shoot at them. 
							 //Sets enemy on alert. Resets the alert_time variable.
	
	bool HitPlayer(WinSprite P); //checks if shot has successfully hit player - collision detection between Player and bullets
	
	void Death(void); //sets the enemy as dead - changes colour to dark grey
	
	void Update(void); //updates position of enemy and enemy bullets - handles Patrol() calls, bullet movement updates, alert status checks
	
	void Reset(void); //resets the enemy variables back to default in order to start new level

	std::vector<WinSprite> Bullets; //vector for holding any bullets fired by this enemy

private:
	//PROTOTYPES///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Patrol(void); //calls the pathfinding algorithm to calculate the patrol route between the two grid squares and executes the next move
		
	void ShootGun(void); //checks the shoot_time variable and if enough time has passed since last shot fired, generates a new bullet
	
	void AlertState(void); //function to set the colour of the eye based on whether or not the enemy is on alert
	
	void Movement(int xx, int yy); //using Bresenham's straight line algorithm to move the enemy one move from current position 
								   //in direction of given coordinates

	void LoadBitMapsandMasks(void); //stores all bitmaps for enemy animations and masks

	HBITMAP LoadABitmap(LPSTR szFileName); //returns an HBITMAP of the provided .bmp file (Matthew Bett's function)

	//VARIABLES/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	HBITMAP animations[7];

	int clr; //checks which colour eyes should be so that correct animation bitmap is used

	int steps; //toggles between walking animation bitmaps

	HBITMAP masks[3];
	
	int shoot_time; //timer used for generating and deleting bullets so that shots are not fired too often 
					//and are removed once they travel a certain distance
					
	bool alert; //bool used to check if enemy is alerted or not
	
	bool dead; //bool used to check if enemy is still alive
	
	int pat_a1, pat_b1, pat_a2, pat_b2;  //start and end grid coordinates for enemy's patrol path

	int wait_time; //variable used to determine how long the enemy stops at either end of their patrol route before moving again
	
	PathFinder patrol; //pathfinder object used when generating the best path between the two patrol route end points
					   //PathFinder class contains an a* pathfinding algorithm which fills a vector with the resultant path
	
	bool patrolling; //bool used to check if enemy is currently moving on their patrol or waiting at either end
	
	int tt; //timer variable used to compare time waited against the set wait_time to see if the enemy should start moving
			
	int alert_time; //timer used to control how long the enemy stays alert after sighting the player. 
	
	int path_iterator; //iterator passed to the GetNextMove(int) function of the pathfinder patrol object to retrieve moves from the vector
					   //containing the patrol path
};


#endif