#include "gamelevels.h"

//LEVELONE() FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameLevels::LevelOne(void)
{
	//CORNERS
	SetScenery(1, 1, TOPLEFTCORNER);
	SetScenery(18, 1, TOPRIGHTCORNER);
	SetScenery(1, 14, BOTTOMLEFTCORNER);
	SetScenery(18, 14, BOTTOMRIGHTCORNER);
	
	//HORIZONTAL WALLS	
	SetScenery(2, 1, HORIZONTAL); //walls along top of play area
	SetScenery(3, 1, HORIZONTAL);

	for(int wh = 5; wh<18; wh++) 
	{
		SetScenery(wh, 1, HORIZONTAL);
	}
	
	for(int wh = 2; wh<10; wh++) //walls along bottom of play area
	{
		SetScenery(wh, 14, HORIZONTAL);
	}
	
	for(int wh = 11; wh<18; wh++) //walls along bottom of play area
	{
		SetScenery(wh, 14, HORIZONTAL);
	}
	
	for(int wh = 6; wh<15; wh++) //walls along centre of play area
	{
		SetScenery(wh, 7, HORIZONTAL);
	}

	for(int wh = 9; wh<12; wh++) //walls along centre of play area
	{
		SetScenery(wh, 12, HORIZONTAL);
	}
		
	//VERTICAL WALLS	
	for(int wv = 2; wv<14; wv++) //walls along left of play area
	{
		SetScenery(1, wv, VERTICAL);
		SetScenery(18, wv, VERTICAL);
	}
	
	//ENTRANCE
	SetScenery(10, 14, STARTH); //entrance
	
	//EXIT
	//open space for level one - nice and easy 
	
	//KEY
	//no key in level one

	//Player and Guard starting positions
	pStartx = Grid[13][10].GetX()-8;
	pStarty = Grid[13][10].GetY()-8;
	g1Pat_a1 = 4;
	g1Pat_b1 = 7;
	g1Pat_a2 = 15;
	g1Pat_b2 = 7;
	g1_time = 400;
	
	guards = 1;
	
	p_ang = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LEVELTWO() FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameLevels::LevelTwo(void)
{

	//CORNERS
	SetScenery(1, 1, TOPLEFTCORNER);
	SetScenery(18, 1, TOPRIGHTCORNER);
	SetScenery(1, 14, BOTTOMLEFTCORNER);
	SetScenery(18, 14, BOTTOMRIGHTCORNER);
	SetScenery(4, 4, TOPLEFTCORNER);
	SetScenery(11, 4, TOPRIGHTCORNER);
	SetScenery(14, 6, TOPLEFTCORNER);
	SetScenery(11, 8, BOTTOMRIGHTCORNER);
	SetScenery(14, 14, BOTTOMRIGHTCORNER);
	SetScenery(14, 14, BOTTOMLEFTCORNER);
	
	//HORIZONTAL WALLS	
	SetScenery(2, 1, HORIZONTAL); //walls along top of play area
	SetScenery(3, 1, HORIZONTAL);
	
	for(int wh = 5; wh<18; wh++) 
	{
		SetScenery(wh, 1, HORIZONTAL);
	}
	
	SetScenery(2, 14, HORIZONTAL); //walls along top of play area
	SetScenery(3, 14, HORIZONTAL);
	
	for(int wh = 5; wh<14; wh++) 
	{
		SetScenery(wh, 14, HORIZONTAL);
	}
	
	for(int wh = 15; wh<18; wh++) 
	{
		SetScenery(wh, 14, HORIZONTAL);
	}
	
	for(int wh = 5; wh<11; wh++) //walls along centre of play area
	{
		SetScenery(wh, 4, HORIZONTAL);
	}
	
	SetScenery(15, 6, HORIZONTAL);

	for(int wh = 7; wh<11; wh++) //walls along centre of play area
	{
		SetScenery(wh, 8, HORIZONTAL);
	}
		
	//VERTICAL WALLS	
	for(int wv = 2; wv<14; wv++) //walls along left of play area
	{
		SetScenery(1, wv, VERTICAL);
		SetScenery(18, wv, VERTICAL);
	}
	
	for(int wv = 5; wv<11; wv++) //5-11 at 4
	{
		SetScenery(4, wv, VERTICAL);
	}
	
	for(int wv = 5; wv<8; wv++) //5-7 at 11
	{
		SetScenery(11, wv, VERTICAL);
	}
	
	for(int wv = 7; wv<14; wv++) //walls down centre of play area
	{
		SetScenery(14, wv, VERTICAL);
	}
	
	//ENTRANCE
	SetScenery(4, 14, STARTH); //entrance
	
	//EXIT
	SetScenery(4, 1, DOORH); //exit
	
	//KEY
	SetScenery(15, 13, KEY);

	//Player and Guard starting positions
	pStartx = Grid[13][4].GetX();
	pStarty = Grid[13][4].GetY();
	g1Pat_a1 = 4;
	g1Pat_b1 = 2;
	g1Pat_a2 = 9;
	g1Pat_b2 = 10;
	g1_time = 350;
	
	guards = 1;
	
	p_ang = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LEVELTHREE() FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameLevels::LevelThree(void)
{
	//CORNERS
	SetScenery(1, 1, TOPLEFTCORNER);
	SetScenery(18, 1, TOPRIGHTCORNER);
	SetScenery(13, 3, TOPLEFTCORNER);
	SetScenery(4, 4, TOPLEFTCORNER);
	SetScenery(13, 6, BOTTOMRIGHTCORNER);
	SetScenery(7, 8, BOTTOMLEFTCORNER);
	SetScenery(15, 8, TOPLEFTCORNER);
	SetScenery(1, 9, BOTTOMLEFTCORNER);
	SetScenery(1, 9, TOPLEFTCORNER);
	SetScenery(11, 10, BOTTOMRIGHTCORNER);
	SetScenery(1, 14, BOTTOMLEFTCORNER);
	SetScenery(7, 14, BOTTOMRIGHTCORNER);
	SetScenery(7, 14, BOTTOMLEFTCORNER);
	SetScenery(18, 14, BOTTOMRIGHTCORNER);
	
	//HORIZONTAL WALLS	
	for(int wh = 2; wh<18; wh++) //walls along top of play area
	{
		SetScenery(wh, 1, HORIZONTAL);
	}
	for(int wh = 2; wh<4; wh++) //walls along bottom of play area
	{
		SetScenery(wh, 9, HORIZONTAL);
		SetScenery(wh, 14, HORIZONTAL);
	}
	for(int wh = 5; wh<7; wh++) //walls along bottom of play area
	{
		SetScenery(wh, 14, HORIZONTAL);
	}
	for(int wh = 8; wh<18; wh++) //walls along bottom of play area
	{
		SetScenery(wh, 14, HORIZONTAL);
	}
	
	SetScenery(14, 3, HORIZONTAL); //14 and 15 at 3 down
	SetScenery(15, 3, HORIZONTAL);
	
	for(int wh = 5; wh<10; wh++) //5-9 at 4 down
	{
		SetScenery(wh, 4, HORIZONTAL);
	}
	
	for(int wh = 10; wh<13; wh++) //10-12 at 6 down
	{
		SetScenery(wh, 6, HORIZONTAL);
	}
	
	SetScenery(8, 8, HORIZONTAL); //8, 9 and 16 at 8 down
	SetScenery(9, 8, HORIZONTAL);
	SetScenery(16, 8, HORIZONTAL);
	
	for(int wh = 8; wh<11; wh++) //8-10 at 10 down
	{
		SetScenery(wh, 10, HORIZONTAL);
	}
	
	//VERTICAL WALLS	
	for(int wv = 2; wv<9; wv++) //walls along left of play area
	{
		SetScenery(1, wv, VERTICAL);
	}
	for(int wv = 10; wv<14; wv++) //walls along left of play area
	{
		SetScenery(1, wv, VERTICAL);
	}
	for(int wv = 2; wv<7; wv++) //walls along right of play area
	{
		SetScenery(18, wv, VERTICAL);
	}
	for(int wv = 8; wv<14; wv++) //walls along right of play area
	{
		SetScenery(18, wv, VERTICAL);
	}
	
	SetScenery(4, 5, VERTICAL); //5 and 6 at 4 across
	SetScenery(4, 6, VERTICAL);
	
	SetScenery(7, 7, VERTICAL); //7, 12 and 13 at 7 across
	SetScenery(7, 12, VERTICAL);
	SetScenery(7, 13, VERTICAL);
	
	SetScenery(11, 9, VERTICAL); //11 at 9 across
	
	SetScenery(13, 4, VERTICAL); //4 and 5 at 13 across
	SetScenery(13, 5, VERTICAL);
	
	for(int wv = 9; wv<13; wv++) //walls along right of play area
	{
		SetScenery(15, wv, VERTICAL);
	}
		
	//ENTRANCE
	SetScenery(4, 14, STARTH); //entrance
	
	//EXIT
	SetScenery(18, 7, DOORV); //exit
	
	//KEY
	SetScenery(12, 5, KEY);

	//Player and Guard starting positions
	pStartx = Grid[13][4].GetX();
	pStarty = Grid[13][4].GetY();
	g1Pat_a1 = 2;
	g1Pat_b1 = 3;
	g1Pat_a2 = 13;
	g1Pat_b2 = 10;
	g1_time = 250;
	g2Pat_a1 = 16;
	g2Pat_b1 = 11;
	g2Pat_a2 = 7;
	g2Pat_b2 = 2;
	g2_time = 350;
	
	guards = 2;
	
	p_ang = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//KEYCOLLECTED() FUNCTION///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameLevels::KeyCollected(void)
{
	Key.clear(); //delete key on level layout
	SetScenery(18, 0, KEY); //draw new key at top right of screen to indicate a key has been collected
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CLEARLEVEL() FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameLevels::ClearLevel(void)
{
	Wall.clear();
	Door.clear();
	Key.clear();
	
	//variables for setting up game grid
	int a = 0;
	int b = 0;
	
	//set centre coordinates for all the grid squares on the screen
	for(int g = 0; g < 320; g++)
	{
		Grid[b][a].blocked = false;
		if(a<19)
		{
			a++;
		}
		else
		{
			a=0;
			if(b<15)
			{
				b++;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SETSCENERY(aa, bb, SceneryType) FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////
void GameLevels::SetScenery(int aa, int bb, TypeofScenery SceneryType)
{
	switch(SceneryType)
	{
		case HORIZONTAL: //draw a horizontal wall in provided grid square
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(32, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-16, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");
			Grid[bb][aa].blocked = true;
			break;

		case VERTICAL: //draw a vertical wall in provided grid square
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 32); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-16); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");
			Grid[bb][aa].blocked = true;
			break;
		
		case DOORV: //draw a vertical door in provided grid square
			Door.push_back(*new WinSprite);
			Door.back().SetDimensions(8, 32); //set width and height for door
			Door.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-16); //position wall at centre positions of grid square
			Grid[bb][aa].blocked = true;
			break;
				
		case DOORH: //draw a vertical Door in provided grid square
			Door.push_back(*new WinSprite);
			Door.back().SetDimensions(32, 8); //set width and height for Doors
			Door.back().MoveTo(Grid[bb][aa].GetX()-16, Grid[bb][aa].GetY()-4); //position Door at centre positions of grid square
			Grid[bb][aa].blocked = true;
			break;
		
		case TOPLEFTCORNER: //draw a corner wall in provided grid square made of 3 sprites
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 16); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(16, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX(), Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Grid[bb][aa].blocked = true;
			break;
		
		case TOPRIGHTCORNER: //draw a corner wall in provided grid square made of 3 sprites
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 16); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(16, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-16, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");
			Grid[bb][aa].blocked = true;
			break;
		
		case BOTTOMLEFTCORNER: //draw a corner wall in provided grid square made of 3 sprites
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 16); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-16); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(16, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX(), Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");
			Grid[bb][aa].blocked = true;
			break;
			
		case BOTTOMRIGHTCORNER: //draw a corner wall in provided grid square made of 3 sprites
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 16); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-16); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(16, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-16, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");

			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");
			Grid[bb][aa].blocked = true;
			break;
			
		case STARTV: //draw a vertical wall in provided grid square - may update to different bitmaps for start points
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(8, 32); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-16); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");
			Grid[bb][aa].blocked = true;
			break;
		
		case STARTH: //draw a vertical wall in provided grid square
			Wall.push_back(*new WinSprite);
			Wall.back().SetDimensions(32, 8); //set width and height for walls
			Wall.back().MoveTo(Grid[bb][aa].GetX()-16, Grid[bb][aa].GetY()-4); //position wall at centre positions of grid square
			Wall.back().SetDisplayBitmap("hedge.bmp");
			Grid[bb][aa].blocked = true;
			break;
			
		case KEY: //draw a key in provided grid square
			//key sprite
			Key.push_back(*new WinSprite);
			Key.back().SetDimensions(8, 14); //set width and height for Key
			Key.back().MoveTo(Grid[bb][aa].GetX()-4, Grid[bb][aa].GetY()-7); //position Key in centre of grid square
			break;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				