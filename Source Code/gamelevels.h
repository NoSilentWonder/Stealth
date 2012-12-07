#ifndef _GAMELEVELS_H_
#define _GAMELEVELS_H_

#include "sprites.h"
#include <vector>
#include "gridspace.h"

//GAMELEVELS CLASS 
//THIS CLASS HAS FUNCTIONS CONTAINING THE LEVEL LAYOUT FOR EACH LEVEL IN THE GAME 
//AND A SETSCENERY FUNCTION WHICH DEFINES THE PARAMETERS FOR EACH TYPE OF SCENERY
//ELEMENT - EG HORIZONTAL/VERTICAL WALLS, DOORS, KEYS.
//IT ALSO SETS START POSITIONS FOR ALL CHARACTERS IN THE LEVEL.
//ALL GAMELEVEL SPRITES ARE CONTAINED IN PUBLIC ACCESS VECTORS FOR EASE OF
//COLLISION DETECTION.
class GameLevels
{
public:
	void LevelOne(void);
	void LevelTwo(void);
	void LevelThree(void);
	void KeyCollected(void);
	void ClearLevel(void);
	
	std::vector<WinSprite> Wall;
	std::vector<WinSprite> Door;
	std::vector<WinSprite> Key;
	
	int pStartx, pStarty; //player starting coordinates
	
	int g1Pat_a1, g1Pat_b1, g1Pat_a2, g1Pat_b2; //guard patrol start and end grid squares and timers
	int g1_time;
	int g2Pat_a1, g2Pat_b1, g2Pat_a2, g2Pat_b2;
	int g2_time;
	
	int guards;
	float p_ang;
	
private:
	enum TypeofScenery
	{
		HORIZONTAL,
		VERTICAL,
		DOORV,
		DOORH,
		TOPLEFTCORNER,
		TOPRIGHTCORNER,
		BOTTOMLEFTCORNER,
		BOTTOMRIGHTCORNER,
		STARTV,
		STARTH,
		KEY
	};
	void SetScenery(int aa, int bb, TypeofScenery SceneryType); //function contains a switch statement to choose the scenery type
	
};


#endif