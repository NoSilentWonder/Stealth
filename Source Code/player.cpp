#include "player.h"
#include "physicseng2d.h"

//PLAYER CONSTRUCTOR///////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(void)
{
	m_x = 0; //positions player at provided parameters
	m_y = 0;

	SetDimensions(16, 16);
	
	SetVelocity(2.0f, 2.0f); //sets the velocity for the player

	Star.MoveTo(-10, -10);
	Star.SetDimensions(6, 6);
	Star.SetVelocity(0, 0);
	
	throw_time = 0; //ready to throw a throwing star
	health = 750; //starts at full health
	key = false; //does not begin with a key
	dead = false; //defaults to alive

	LoadBitMapsandMasks(); //load all the bitmaps and masks for the player animations

	bitmap = animations[0]; //set display bitmap to first bitmap of animation

	clr = 0; //clr variable defaulted to 0 - points to green eyed animations
	steps = 1; 

	bitmask = masks[0]; //set display mask to first mask
	
	Initialise();	
} 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CONTROL(k) FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////
//Function that takes input from the keyboard and moves the player accordingly
void Player::Control(bool k[256])
{
	if(!dead) //make sure player isn't dead
	{
		//move forward/backwards using the up and down arrowkeys
		if(k[38])
		{
			MoveDeltaX((int)(-m_Vy*-sin(PI*m_rota/180))); //player can only move directly forwards or backwards
			MoveDeltaY((int)(-m_Vy*cos(PI*m_rota/180)));  //adjusted for direction they are facing and their set velocity 

			bitmap = animations[steps+clr];
			if(m_rota>175 && m_rota<185)
				bitmask = masks[3];
			else
			{
				bitmask = masks[steps];
			}
			if(steps == 1)
			{
				steps = 2;
			}
			else
			{
				steps = 1;
			}
		}
		else if(k[40])
		{
			MoveDeltaX((int)(m_Vy*-sin(PI*m_rota/180))); //player can only move directly forwards or backwards
			MoveDeltaY((int)(m_Vy*cos(PI*m_rota/180)));  //adjusted for direction they are facing and their set velocity 

			bitmap = animations[steps+clr];
			if(m_rota>175 && m_rota<185)
				bitmask = masks[3];
			else
			{
				bitmask = masks[steps];
			}
			if(steps == 1)
			{
				steps = 2;
			}
			else
			{
				steps = 1;
			}
		}
		else
		{
			bitmap = animations[0+clr];
			if(m_rota>175 && m_rota<185)
				bitmask = masks[3];
			else
			{
				bitmask = masks[0];
			}
		}

		//rotate using the left and right arrowkeys
		if(k[37])
		{
			Rotate(-3.0f);
		}

		if(k[39])
		{
			Rotate(3.0f);
		}

		if(k[32])
		{
			if(throw_time == 0) //check if a star has already been thrown
			{
				throw_time = 20; //sets time for new throw
				Star.SetVelocity(6*sin(PI*m_rota/180), 6*-cos(PI*m_rota/180));  //set velocity of star to 4 

				Star.MoveTo(m_cx-2, m_cy-2);   //move to centre of player
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//HITENEMY(E) FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////
bool Player::HitEnemy(WinSprite E)
{
	if(PhysicsEng::HitBox(E, Star))
	{
		Star.MoveTo(-10, -10);
		Star.SetVelocity(0, 0);
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SHOT() FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::Shot(void)
{
	health -= 150;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//HASKEY() FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////
bool Player::HasKey(void)
{
	return key;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PICKUPKEY() FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////
void Player::PickUpKey(void)
{
	key = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//GAMEWON() FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////
bool Player::GameWon(void)
{
	if((grid_a < 1) || (grid_a > 18) || (grid_b < 1) || (grid_b > 14))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//GAMELOST() FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////
bool Player::GameLost(void)
{
	if(dead)
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//UPDATE() FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////
//updates the player information
void Player::Update(void)
{	
	//update health and health display
	HealthDisplay();
	if(health<750 && health>0)
	{
		health++;
	}
	if(health<=0)
	{
		Death();
	}
	
	//update position of throwing star if it is active
	if(throw_time>0)
	{
		Star.Move();         //move and rotate star for set time
		Star.Rotate(15);
		throw_time--;
	}
	else
	{
		Star.MoveTo(-10, -10);
		Star.SetVelocity(0, 0);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//RESET() FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::Reset(void) //if health reaches 0, player dies
{
	m_x = 500; //positions player off screen
	m_y = 500;
	
	throw_time = 0; //ready to throw a throwing star
	health = 750; //starts at full health
	key = false; //does not begin with a key
	dead = false; //defaults to alive

	clr = 0;
	bitmap = animations[0+clr];
	if(m_rota>175 && m_rota<185)
		bitmask = masks[3];
	else
	{
		bitmask = masks[0];
	}
	
	Star.MoveTo(-10, -10);
	Star.SetVelocity(0, 0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LOADBITMAPSANDMASKS() FUNCTION/////////////////////////////////////////////////////////////////////////////////////////
void Player::LoadBitMapsandMasks(void)
{
	animations[0] = LoadABitmap("grnstill.bmp");
	animations[1] = LoadABitmap("grnwlk1.bmp");
	animations[2] = LoadABitmap("grnwlk2.bmp");

	animations[3] = LoadABitmap("ylwstill.bmp");
	animations[4] = LoadABitmap("ylwwlk1.bmp");
	animations[5] = LoadABitmap("ylwwlk2.bmp");

	animations[6] = LoadABitmap("orgstill.bmp");
	animations[7] = LoadABitmap("orgwlk1.bmp");
	animations[8] = LoadABitmap("orgwlk2.bmp");

	animations[9] = LoadABitmap("redstill.bmp");
	animations[10] = LoadABitmap("redwlk1.bmp");
	animations[11] = LoadABitmap("redwlk2.bmp");

	animations[12] = LoadABitmap("dead.bmp");

	masks[0] = LoadABitmap("maskstill.bmp");
	masks[1] = LoadABitmap("maskwalk1.bmp");
	masks[2] = LoadABitmap("maskwalk2.bmp");
	masks[3] = LoadABitmap("maskupdown.bmp");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//HEALTHDISPLAY() FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////
//Function to change the colour of the player eye to act as a health indicator
void Player::HealthDisplay(void)
{
	if(health>=500)
	{
		clr = 0;    //set eye to green is health is high
	}
	if(health<375 && health>=250)
	{
		clr = 3;  //set eye to yellow if moderate damage taken
	}
	if(health<250 && health>=175)
	{
		clr = 6;   //set eye to orange if high damage taken
	}
	if(health<175 && health>0)
	{
		clr = 9;    //set eye to red if critical damage taken (death imminent)
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//DEATH() FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////
void Player::Death(void) //if health reaches 0, player dies
{
	clr = 12;
	bitmap = animations[0+clr];
	if(m_rota>175 && m_rota<185)
		bitmask = masks[3];
	else
	{
		bitmask = masks[0];
	}
	dead = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

//LOADABITMAP(szFileName) FUNCTION///////////////////////////////////////////////////////////////////////////////////////
HBITMAP Player::LoadABitmap(LPSTR szFileName)
{
	return (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
