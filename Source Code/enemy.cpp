#include "enemy.h"
#include "math.h"
#include "physicseng2d.h"
#include <vector>

//ENEMY() CONSTRUCTOR/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Enemy::Enemy(void)
{
	m_x = 0;  //starting coordinates default to 0, 0.
	m_y = 0;
	
	SetDimensions(16, 16);

	pat_a1 = pat_a2 = 0; //defaults to having no set path
	pat_b1 = pat_b2 = 0;
	
	wait_time = 500; //default wait time for patrolling of 500
	
	patrolling = false; //enemy will begin by waiting at the start of their patrol route before moving
	tt = 0;             //timer starts at 0 and will count to wait_time before enemy begins to patrol
	
	shoot_time = 0;
	alert = false; //default to not on alert (player not sighted)
	dead = false; //default to alive

	LoadBitMapsandMasks(); //load all the bitmaps and masks for the player animations

	bitmap = animations[0]; //set display bitmap to first bitmap of animation

	clr = 0; //clr variable defaulted to 0 - points to green eyed animations
	steps = 0; 

	bitmask = masks[0]; //set display mask to first mask
	
	Initialise(); //this calculates all the corner positions for the sprite, sets its rotation (0 by default), and sets it as white
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//**************************************PUBLIC FUNCTIONS FOR ENEMY CLASS********************************************************************



//SETPATROL(A1, B1, A2, B2) FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////
//sets start and end point for enemy's patrol route and a wait time for them to pause before patrolling
void Enemy::SetPatrol(int a1, int b1, int a2, int b2, int t)
{
	path_iterator = 0; //set iterator to 0 so Patrol() will read path from the beginning
	pat_a1 = a1;
	pat_b1 = b1;
	pat_a2 = a2;
	pat_b2 = b2;
	m_x = Grid[b1][a1].GetX() - 8; //moves enemy to the centre for the starting grid square on their patrol route
	m_y = Grid[b1][a1].GetY() - 8;		
	wait_time = t;
	patrol.SetUp(pat_a1, pat_b1, pat_a2, pat_b2); //passes patrol start and end points to pathfinder object
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//CHASE(PLAYER) FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Chase(WinSprite P)
{
	if(!dead) //check if enemy dead - enemy won't react to player if dead
	{
		alert = true;
		alert_time = 500;
		
		//calculate angle that player position is from enemy
		float angle = atan2((float)(P.GetY() - m_y),(float)(P.GetX() - m_x)) * 180 / PI + 90;
		//make sure the angle is between 0 and 360
		while((angle>360) || (angle<0))
		{
			angle -= angle > 360 ? 360 : 0;
			angle += angle < 0 ? 360 : 0; 
		}
		
		//rotate to face player and shoot them
		SetRotation(angle);
		ShootGun();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//HIPLAYER(PLAYER) FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Enemy::HitPlayer(WinSprite P)
{
	for(int bullets = 0; bullets < Bullets.size(); bullets++) //check all bullets in bullets vector
	{
		if(PhysicsEng::HitBox(P, Bullets[bullets]))  //collision check against player
		{
			Bullets.erase(Bullets.begin()+bullets);   //erase bullet if it has hit
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//DEATH() FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Death(void) //enemy dies if they are shot by player
{
	dead = true;
	clr = 6;
	steps = 0;
}	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//UPDATE() FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//updates the enemy information
void Enemy::Update(void)
{	
	bitmap = animations[steps+clr];
	bitmask = masks[steps];
	if(!dead)
	{
		AlertState(); //update eye colour using alert status
		
		if(alert)
		{
			steps = 0;
			alert_time--; //decrease alert time while alert
			if(alert_time < 450)
			{
				Rotate(-1); //rotate enemy (searching) if currently alert but enemy no longer in line of sight
			}
			
			if(alert_time == 0)
				alert = false; //stand down from alert if enemy not sighted again, resume patrolling
		}
		else
		{
			Patrol(); //handles enemy pathfinding and movement
		}
	}
	
	//update position of bullets if enemy is firing
	if(shoot_time>0)
	{
		for(int blts = 0; blts<Bullets.size(); blts++)
		{
			Bullets[blts].Move();    //move bullets at set velocity
		}
		shoot_time--;
	}
	else
	{
		Bullets.clear();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//RESET() FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::Reset(void)
{
	m_x = 500;  //move enemy off the screen
	m_y = 500;
	
	patrolling = false; //enemy will begin by waiting at the start of their patrol route before moving
	tt = 0;             //timer starts at 0 and will count to wait_time before enemy begins to patrol

	shoot_time = 0;
	alert = false; //default to not on alert (player not sighted)
	dead = false; //default to alive
	
	clr = 0;
	steps = 0;
	bitmap = animations[steps+clr];
	bitmask = masks[0];

	Bullets.clear(); //clear any bullets
	
	patrol.ClearVectors(); //clear the stored path
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//**************************************PRIVATE FUNCTIONS FOR ENEMY CLASS********************************************************************


//PATROL FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//find a path between the given patrol start and end points
void Enemy::Patrol(void)
{		
	//variables
	int move_a, move_b; //grid references
	int move_x, move_y; //actual coordinates
	
	//timer tt will increase each game loop until wait_time has been reached
	//enemy will also rotate while waiting at start of patrol route to add some movement/risk for the player (changing enemy los)
	if(tt<wait_time)
	{
		tt++;
		Rotate(1);
		steps = 0;
	}
	
	//handles enemy movement when finished waiting
	else
	{
		//has enemy already started patrolling
		if(!patrolling) 
		{
			patrol.ClearVectors(); //clear the stored path
			//findThePath() will run a* pathfinding algorithm and fill the path vector with resultant path 
			//returns false if start and end provided are the same
			if(patrol.findThePath()) //if a path exists (patrol start and end are different)
			{
				patrolling = true; //begin enemy patrolling
				steps = 1;
			}
		}
		
		//enemy is now patrolling - a path has been generated to follow
		else
		{	
			if(path_iterator != patrol.getPathSize()) //check if the end of the patrol is reached
			{
				Path nextMove = patrol.getNextMove(path_iterator); //retrieve next move from vector containing path
				move_a = nextMove.a; //set grid references for next move
				move_b = nextMove.b;
				move_x = Grid[move_b][move_a].GetX() - 8; //set actual coordinates for centre of next grid square
				move_y = Grid[move_b][move_a].GetY() - 8;
				
				if((m_x == move_x) && (m_y == move_y)) //check if enemy has reached next move
				{
					path_iterator++; //get next move
				}
				else //if enemy is not at next move position yet
				{				
					//find angle between enemy's current position and next grid square
					float angle = atan2((float)(move_y - m_y),(float)(move_x - m_x))* 180 / PI + 90;
					//make sure the angle is between 0 and 360
					while((angle>360) || (angle<0))
					{
						angle -= angle > 360 ? 360 : 0;
						angle += angle < 0 ? 360 : 0; 
					}
					SetRotation(angle); //rotate enemy to face next position
			
					Movement(move_x, move_y);
					if(steps == 1)
					{
						steps = 2;
					}
					else
					{
						steps = 1;
					}
				}
			}
			//enemy has reached end of patrol route
			else
			{
				patrolling = false; //no longer patrolling
				tt = 0; //reset timer
				patrol.ClearVectors(); //clear the stored path
				SetPatrol(pat_a2, pat_b2, pat_a1, pat_b1, wait_time); //reverse patrol route
			}
		}
	}
}	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SHOOTGUN() FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//controls the starting position and velocity of bullets when fired
void Enemy::ShootGun(void)
{
	if(shoot_time == 0) //check if a bullet has already been fired
	{
		shoot_time = 25; //sets time for new shot
		Bullets.push_back(*new WinSprite); //create new bullet and add to bullets vector
		Bullets.back().SetVelocity(10*sin(PI*m_rota/180), 10*-cos(PI*m_rota/180));  //set velocity of bullet to 7 in the direction enemy is facing
		Bullets.back().SetDimensions(4, 8);
		Bullets.back().MoveTo(m_cx-2, m_cy-4);   //move to centre of enemy
		Bullets.back().SetRotation(m_rota); //match enemy's rotation
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ALERTSTATE() FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Enemy::AlertState(void)
{
	if(alert)
	{
		clr = 3; //red
	}
	else
	{
		clr = 0; //green
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//MOVEMENT(XX, YY) FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Bresenham's line algorithm - used to work out the next point of movement in a straight line from current position to a given point (xx, yy)
//this is based on the algorithm from J. Harbour's book
void Enemy::Movement(int xx, int yy)
{
	if(m_x > xx)
		m_x-= 1;
	if(m_x < xx)
		m_x+= 1;

	if(m_y > yy)
		m_y -= 1;
	if(m_y < yy)
		m_y += 1;
 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LOADBITMAPSANDMASKS() FUNCTION/////////////////////////////////////////////////////////////////////////////////////////
void Enemy::LoadBitMapsandMasks(void)
{
	animations[0] = LoadABitmap("egrnstill.bmp");
	animations[1] = LoadABitmap("egrnwlk1.bmp");
	animations[2] = LoadABitmap("egrnwlk2.bmp");

	animations[3] = LoadABitmap("eredstill.bmp");
	animations[4] = LoadABitmap("eredwlk1.bmp");
	animations[5] = LoadABitmap("eredwlk2.bmp");

	animations[6] = LoadABitmap("dead.bmp");

	masks[0] = LoadABitmap("maskstill.bmp");
	masks[1] = LoadABitmap("maskwalk1.bmp");
	masks[2] = LoadABitmap("maskwalk2.bmp");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LOADABITMAP(szFileName) FUNCTION///////////////////////////////////////////////////////////////////////////////////////
HBITMAP Enemy::LoadABitmap(LPSTR szFileName)
{
	return (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
