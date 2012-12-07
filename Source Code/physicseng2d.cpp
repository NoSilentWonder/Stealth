#include "physicseng2d.h"
#include "math.h"

#define PI 3.14159265359
//**************************************COLLISION DETECTION ALGORITHMS**********************************************************************

//HITBOX(S1, S2) FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PhysicsEng::HitBox(WinSprite &S1, WinSprite &S2)
{
	if((S1.GetX() + S1.GetWidth()-2) < S2.GetX())
		return false;
	if(S1.GetX() > (S2.GetX() + S2.GetWidth()-2))
		return false;
	if((S1.GetY() + S1.GetHeight()-2) < S2.GetY())
		return false;
	if(S1.GetY() > (S2.GetY() + S2.GetHeight()-2))
		return false;
	else
	{
		return true;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//HITCIRCLE(S1, S2) FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PhysicsEng::HitCircle(WinSprite &S1, WinSprite &S2)
{
	if((pow((float)(S2.GetCentreX() - S1.GetCentreX()), 2)+pow((float)(S2.GetCentreY() - S1.GetCentreY()), 2)) 
	< pow((float)(S1.GetRadius() + S2.GetRadius()), 2))
		return true;
	else
	{
		return false;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LINEOFSIGHT(E, P) FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PhysicsEng::LineOfSight(Enemy &E, Player &P)
{
	//check if player is within 25 radii of enemy. If not, return 0
	if((pow((float)(P.GetCentreX() - E.GetCentreX()), 2)+pow((float)(P.GetCentreY() - E.GetCentreY()), 2)) 
	> pow((float)(E.GetRadius()*25 + P.GetRadius()), 2)) 
	{
		return 0;
	}
	else
	{
		//calculate angle that player position is from enemy
		float angle = atan2((float)(P.GetCentreY() - E.GetCentreY()),(float)(P.GetCentreX() - E.GetCentreX())) * 180 / PI + 90;
		//make sure the angle is between 0 and 360
		while((angle>360) || (angle<0))
		{
			angle -= angle > 360 ? 360 : 0;
			angle += angle < 0 ? 360 : 0; 
		}
		//check player's angle from enemy against direction enemy is facing
		//if player is within 85 degrees of the angle enemy is facing and there are blocks near them return 2 - may be in line of sight
		if((E.GetRotation()<(angle+85))&&E.GetRotation()>(angle-85))
		{
			if(!CheckGridSpaces(E, P)) //no blocks, definitely in line of sight - return 1
				return 1;
			else
			{
				return 2;
			}
		}
		else
		{
			//check if player is within 3 radii of enemy. If it is, return 2 - player close enough to detect
			if((pow((float)(P.GetCentreX() - E.GetCentreX()), 2)+pow((float)(P.GetCentreY() - E.GetCentreY()), 2)) 
			< pow((float)(E.GetRadius()*3 + P.GetRadius()), 2))
			{
				if(!CheckGridSpaces(E, P)) //no blocks, definitely in line of sight - return 1
					return 1;
				else
				{
					return 2;
				}
			}
			else
			{
				return 0;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CHECKGRIDSPACES(E, P) FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PhysicsEng::CheckGridSpaces(Enemy &E, Player &P)
{
	int e_a = E.GetGrid_a();
	int e_b = E.GetGrid_b();
	int p_a = P.GetGrid_a();
	int p_b = P.GetGrid_b();
	
	int min_a = e_a < p_a ? e_a : p_a;
	int max_a = e_a > p_a ? e_a : p_a;
	int min_b = e_b < p_b ? e_b : p_b;
	int max_b = e_b > p_b ? e_b : p_b;
	
	for(int a = min_a; a < max_a+1; a++)
	{
		for(int b = min_b; b < max_b+1; b++)
		{
			if(Grid[b][a].blocked)
			{
				return true;
			}
		}
	}
	return false;				
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ISLOSBLOCKED(E, P, W) FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PhysicsEng::IsLoSClear(Enemy &E, Player &P, WinSprite W)
{

	int LoSX, LoSY; //point on line
	
	int i, deltax, deltay, pixels;
    int d, dinc1, dinc2;
    int xinc1, xinc2;
    int yinc1, yinc2;

	deltax = abs(P.GetCentreX() - E.GetCentreX());
	deltay = abs(P.GetCentreY() - E.GetCentreY());

	//initialise
	if(deltax >= deltay){
		//If x is independent variable
		pixels = deltax + 1;
		d = (deltay << 1) - deltax;
		dinc1 = deltay << 1;
		dinc2 = (deltay - deltax) << 1;
		xinc1 = 1;
		xinc2 = 1;
		yinc1 = 0;
		yinc2 = 1;
	}
	else
	{
		//if y is independent variable
		pixels = deltay + 1;
		d = (deltax << 1) - deltay;
		dinc1 = deltax << 1;
		dinc2 = (deltax - deltay) << 1;
		xinc1 = 0;
		xinc2 = 1;
		yinc1 = 1;
		yinc2 = 1;
	}
	//move the right direction
	if(E.GetCentreX()>P.GetCentreX())
	{
		xinc1 = -xinc1;
		xinc2 = -xinc2;
	}
	if(E.GetCentreY()>P.GetCentreY())
	{
		yinc1 = -yinc1;
		yinc2 = -yinc2;
	}
	LoSX = (int)E.GetCentreX();
	LoSY = (int)E.GetCentreY();

	for(i = 1; i < pixels; i++) //iterate down a direct line from enemy at given angle
	{
		if(d < 0)
		{
			d += dinc1;
			LoSX += xinc1;
			LoSY += yinc1;
		}
		else
		{
			d += dinc2;
			LoSX += xinc2;
			LoSY += yinc2;
		} 
		
		if(i/4 == 0) //only check every 4 pixels - this will still hit a wall if one is present
		{
			if((LoSX > W.GetX()) &&  //if point on line of enemy's sight hits a wall, stop checking that line
			(LoSX < (W.GetX() + W.GetWidth())) &&
			(LoSY > W.GetY()) &&
			(LoSY < (W.GetY() + W.GetHeight())))
				return false;
		}
		
	}
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//HITWALL(Spr) FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PhysicsEng::HitWall(WinSprite &Spr)
{
	// Make sure the sprite stops if it hits the edge of the screen
	if ((Spr.GetX() + Spr.GetWidth())>640)
	{
		NoGo(Spr);
		Spr.Rotate(180);
	}
	if (Spr.GetX()<0)
	{
		NoGo(Spr);
		Spr.Rotate(180);
	}
	if (Spr.GetY()>512)
	{
		NoGo(Spr);
		Spr.Rotate(180);
	}
	if (Spr.GetY()<0)
	{
		NoGo(Spr);
		Spr.Rotate(180);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//NOGO(S) FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PhysicsEng::NoGo(WinSprite &S)
{
	S.MoveTo(S.GetPrevX(), S.GetPrevY());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//UNLOCKDOOR(door) FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PhysicsEng::UnlockDoor(WinSprite & door)
{
	door.Rotate(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
