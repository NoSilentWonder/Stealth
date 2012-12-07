#include "sprites.h"
#include "player.h"
#include "gridspace.h"
#include "enemy.h"
#include <fstream>
#include "physicseng2d.h"
#include "gamelevels.h"
#include "textsprites.h"

using namespace std;

#pragma comment(lib, "winmm.lib")

#define SCREENWIDTH  640
#define SCREENHEIGHT 512

HBITMAP		theOldFrontBitMap, theOldBackBitMap;
HWND        ghwnd;
RECT		screenRect;
HDC			backHDC, frontHDC, bitmapHDC;	//Hardware device contexts for the Buffers

typedef struct Mouse
{
	int x,y;
}Mouse;
bool mleft = false;
bool mright = false;
bool mmiddle = false;

int xpos, ypos;
int ticker =0;

bool keys[256];

Mouse MousePos;

void RegisterMyWindow(HINSTANCE hInstance);
BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow);
BOOL WaitFor(unsigned long delay);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void setBuffers();
void displayFrame();
void releaseResources();

bool g_bLoop = true;

void sig_handle(int sig)
{
	g_bLoop = false;
}

//STEALTH CLASS CALLS GAME LOGIC FUNCTION
class Stealth
{
public:
	Stealth();
	void GameLogic();
	
private:
	void DrawSprite(WinSprite theSprite);
	void DrawAnimatedSprite(WinSprite theSprite);

	enum GAMESTATE //Game states
	{                          
		FRONT,
		MENU,
		INSTRUCTIONS,
		PLAY,
		LOSE,
		WIN,
		COMPLETE
	};

	//VARIABLES
	GAMESTATE current_state; //current_state used to track if player is playing a level or on a game menu screen.
	ofstream out; //outgoing file data
	int menu_pointer; //used to control the y-position of the option menus 
	int NumofLevels;
	bool paused;
	int lvl;
	int numofguards;

	GameLevels level;  //game objects
	Player player;
	Enemy guard[2];

	//sprites
	WinSprite title;
	WinSprite options;
	TextSprite newgame;
	TextSprite loadgame;
	TextSprite instrn;
	WinSprite instructions;
	WinSprite lvlone;
	WinSprite lvltwo;
	WinSprite lvlthree;
	WinSprite died;
	TextSprite tryagain;
	TextSprite exit;
	WinSprite lvlcomp;
	TextSprite nextlvl;
	WinSprite congrats;
	WinSprite black;
	WinSprite floor;
};

//MAIN FUNCTION////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int nCmdShow)			
{									
    MSG msg;	
	HDC	hdcWindow;

	//variables for setting up game grid
	int a = 0;
	int b = 0;
	
	//set centre coordinates for all the grid squares on the screen
	for(int g = 0; g < 320; g++)
	{
		Grid[b][a].SetCoordinates(a, b);
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

	Stealth stealth;

	RegisterMyWindow(hInstance);

   	if (!InitialiseMyWindow(hInstance, nCmdShow))
		return FALSE;
	
	setBuffers();
		
	//GAME LOOP
	while(g_bLoop) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		    if (msg.message==WM_QUIT)
				break;
			TranslateMessage (&msg);							
			DispatchMessage (&msg);
		}

		else
		{	
			stealth.GameLogic();
		}
    }

    releaseResources();
	return msg.wParam ;										
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//STEALTH CLASS//

//Stealth constructor - sets up all initial variable values and menu sprites
Stealth::Stealth()
{
	current_state = FRONT; //current_state used to track if player is playing a level or on a game menu screen. Always loads front end screen first
	menu_pointer = -100; //used to control the y-position of the option menus 
	NumofLevels = 3;
	paused = false;
	lvl = 0;
	numofguards = 0;

	//sets bitmaps/positions/dimensions for text and menu sprites
	title.SetDimensions(540, 125);
	title.MoveTo(50, 180);
	title.SetDisplayBitmap("title.bmp");

	options.SetDimensions(540, 100);
	options.MoveTo(115, 130);
	options.SetDisplayBitmap("options.bmp");

	newgame.SetDimensions(130, 45);
	newgame.MoveTo(245, 200);
	newgame.LoadBitMaps("newgamen.bmp", "newgameh.bmp");
	
	loadgame.SetDimensions(150, 45);
	loadgame.MoveTo(235, 250);
	loadgame.LoadBitMaps("loadgamen.bmp", "loadgameh.bmp");
	
	instrn.SetDimensions(230, 45);
	instrn.MoveTo(210, 300);
	instrn.LoadBitMaps("instrn.bmp", "instrh.bmp");
	
	instructions.SetDimensions(640, 500);
	instructions.MoveTo(0, 50);
	instructions.SetDisplayBitmap("instructions.bmp");
	
	lvlone.SetDimensions(225, 42);
	lvlone.MoveTo(220, 180);
	lvlone.SetDisplayBitmap("lvlone.bmp");
	
	lvltwo.SetDimensions(225, 42);
	lvltwo.MoveTo(220, 180);
	lvltwo.SetDisplayBitmap("lvltwo.bmp");

	lvlthree.SetDimensions(225, 42);
	lvlthree.MoveTo(200, 180);
	lvlthree.SetDisplayBitmap("lvlthree.bmp");
	
	died.SetDimensions(540, 100);
	died.MoveTo(205, 130);
	died.SetDisplayBitmap("died.bmp");
	
	tryagain.SetDimensions(145, 45);
	tryagain.MoveTo(240, 200);
	tryagain.LoadBitMaps("tryagainn.bmp", "tryagainh.bmp");

	exit.SetDimensions(150, 45);
	exit.MoveTo(275, 250);
	exit.LoadBitMaps("exitn.bmp", "exith.bmp");
	
	lvlcomp.SetDimensions(540, 100);
	lvlcomp.MoveTo(135, 130);
	lvlcomp.SetDisplayBitmap("lvlcomp.bmp");
	
	nextlvl.SetDimensions(155, 45);
	nextlvl.MoveTo(230, 200);
	nextlvl.LoadBitMaps("nextlvln.bmp", "nextlvlh.bmp");

	congrats.SetDimensions(540, 400);
	congrats.MoveTo(105, 130);
	congrats.SetDisplayBitmap("congrats.bmp");
	
	black.MoveTo(0,0);
	black.SetDimensions(640, 512);
	black.SetDisplayBitmap("black.bmp");
	
	floor.MoveTo(0,0);
	floor.SetDimensions(640, 512);
	floor.SetDisplayBitmap("floor.bmp");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//STEALTH::GAMELOGIC() FUNCTION///////////////////////////////////////////////////////////////////////////////
void Stealth::GameLogic()
{
	switch(current_state) //switch statement controlling what state the game is in - playing a level, on a menu etc.
	{
	//**********************************************FRONT END SCREEN**********************************************//
		case FRONT:
			if(mleft)
			{
				mleft = false;
				lvl = 0;
				current_state = MENU;
			}
				
			if(WaitFor(15))
			{
				DrawSprite(black);
				DrawSprite(title);
				displayFrame();
			}
			break;
			
	//**********************************************OPTIONS MENU****************************************************//
		case MENU:
			
			switch(lvl)
			{
				case 0:
					if(MousePos.y > 200 && MousePos.y < 250)
					{
						newgame.Highlight();
						if(mleft)
						{
							mleft = false;
							lvl = 1;
						}
					}
					else
					{
						newgame.Unhighlight();
					}

					if(MousePos.y > 250 && MousePos.y < 300)
					{
						loadgame.Highlight();
						if(mleft)
						{
							mleft = false;
							ifstream in; //incoming file data
							in.open("currentlevel.txt", ios::in); //open currentlevel file
							in >> lvl; //load saved lvl variable
							in.close(); //close file
							if(lvl == 0)
							{
								MessageBox(ghwnd, "No level saved.", "", MB_ICONEXCLAMATION);
							}
						}
					}
					else
					{
						loadgame.Unhighlight();
					}

					if(MousePos.y > 300 && MousePos.y < 350)
					{
						instrn.Highlight();
						if(mleft)
						{
							mleft = false;
							current_state = INSTRUCTIONS;
						}
					}
					else
					{
						instrn.Unhighlight();
					}


					if(WaitFor(15))
					{
						DrawSprite(black);
						DrawSprite(options);
						DrawSprite(newgame);
						DrawSprite(loadgame);
						DrawSprite(instrn);
						displayFrame();
					}
					break;
					
				case 1:
					level.LevelOne();

					player.MoveTo(level.pStartx,level.pStarty);

					guard[0].SetPatrol(level.g1Pat_a1, level.g1Pat_b1, level.g1Pat_a2, level.g1Pat_b2, level.g1_time);
											
					numofguards = level.guards;
					player.SetRotation(level.p_ang);

					player.Star.SetDisplayBitmap("star.bmp");
					
					DrawSprite(black);
					DrawSprite(lvlone);
					displayFrame();

					if(WaitFor(1500))
					{							
						current_state = PLAY;
					}
					break;
					
				case 2:
					level.LevelTwo();

					player.MoveTo(level.pStartx,level.pStarty);

					guard[0].SetPatrol(level.g1Pat_a1, level.g1Pat_b1, level.g1Pat_a2, level.g1Pat_b2, level.g1_time);
					
					numofguards = level.guards;
					player.SetRotation(level.p_ang);


					level.Door[0].SetDisplayBitmap("door.bmp");

					level.Key[0].SetDisplayBitmap("key.bmp");
					level.Key[0].SetDisplayBitmask("maskkey.bmp");

					player.Star.SetDisplayBitmap("star.bmp");

					DrawSprite(black);
					DrawSprite(lvltwo);
					displayFrame();

					if(WaitFor(1500))
					{							
						current_state = PLAY;
					}
					break;
					
				case 3:
					level.LevelThree();

					player.MoveTo(level.pStartx,level.pStarty);

					guard[0].SetPatrol(level.g1Pat_a1, level.g1Pat_b1, level.g1Pat_a2, level.g1Pat_b2, level.g1_time);
					guard[1].SetPatrol(level.g2Pat_a1, level.g2Pat_b1, level.g2Pat_a2, level.g2Pat_b2, level.g2_time);
					
					numofguards = level.guards;
					player.SetRotation(level.p_ang);

					level.Door[0].SetDisplayBitmap("door.bmp");

					level.Key[0].SetDisplayBitmap("key.bmp");
					level.Key[0].SetDisplayBitmask("maskkey.bmp");

					player.Star.SetDisplayBitmap("star.bmp");

					DrawSprite(black);
					DrawSprite(lvlthree);
					displayFrame();
					if(WaitFor(1500))
					{							
						current_state = PLAY;
					}
					break;
			}

			break;
			
	//*******************************************INSTRUCTIONS SCREEN****************************************************//
		case INSTRUCTIONS:
			
			if(mleft)
			{
				mleft = false;
				lvl = 0;
				current_state = MENU;
			}
				
			if(WaitFor(15))
			{
				DrawSprite(black);
				DrawSprite(instructions);
				displayFrame();
			}		
			break;
	
	//**********************************************PLAYING A LEVEL****************************************************//
		case PLAY:				
		
			if(WaitFor(15))
			{
				if(!paused)
				{
				
					if(keys[80])
					{
						keys[80] = false;
						paused = true;
					}
					//PLAYER CONTROLS
					player.Control(keys);  //check input for player movement
					
					//COLLISION DETECTIONS FOR GUARDS
					for(int g = 0; g<numofguards; g++)
					{				
						if(PhysicsEng::LineOfSight(guard[g], player) == 1) //is player too close to enemy
						{
							guard[g].Chase(player);
						}
						
						if(PhysicsEng::LineOfSight(guard[g], player) == 2) //could player be in enemy line of sight
						{
							for(int w = 0; w < level.Wall.size(); w++)
							{
								if(!PhysicsEng::IsLoSClear(guard[g], player, level.Wall[w])) //is enemy line of sight blocked
								{
									guard[g].Chase(player);
								}
							}
						}
					
						if(guard[g].HitPlayer(player)) //has guard shot player
						{
							player.Shot();
						}
					}
					
					//COLLISION DETECTIONS FOR PLAYER
					for(int wall = 0; wall < level.Wall.size(); wall++) //check for player collision with walls - result is always no-go
					{
						if(PhysicsEng::HitBox(player, level.Wall[wall]))
						{
							PhysicsEng::NoGo(player);
						}
						if(PhysicsEng::HitCircle(level.Wall[wall], player.Star))
						{
							player.Star.MoveTo(-10, -10);
							player.Star.SetVelocity(0, 0);
						}
					}
					for(int key = 0; key < level.Key.size(); key++)	//check if player collides with key - will pick up key

					{
						if(PhysicsEng::HitBox(player, level.Key[key]))
						{
							player.PickUpKey();
							level.KeyCollected();
						}
					}
							
					for(int door = 0; door < level.Door.size(); door++) //check for collision with door
					{
						if(PhysicsEng::HitBox(player, level.Door[door]))
						{
							if(player.HasKey()) //if player has already picked up the key
							{
								PhysicsEng::UnlockDoor(level.Door[door]); //animate door - unlock door animation scales down and rotates
								if(level.Door[door].GetRotation() > 180) //delete door when fully rotated
									level.Door.clear();
							}
							PhysicsEng::NoGo(player); //player cannot go through locked door or unlocked door until it has completely disappeared
						}
					}
					
					for(int g = 0; g<numofguards; g++)
					{
						if(player.HitEnemy(guard[g])) //has player shot a guard
						{
							guard[g].Death();
						}
					}
					
					//UPDATE ALL THE ELEMENT POSITIONS AND STATES
					player.Update();
					for(int g = 0; g<numofguards; g++)
					{
						guard[g].Update();
					}
					
					//CHECK FOR EXIT CONDITIONS
					if(player.GameWon()) //GameWon() checks player location. If outside map area, they've gone through the exit
					{
						mleft = false;
						level.ClearLevel();
						player.Reset();
						for(int g = 0; g<2; g++)
						{
							guard[g].Reset();
						}
						menu_pointer = -100;
						if(lvl < NumofLevels)
							current_state = WIN;
						else
						{
							current_state = COMPLETE;
						}
					}
					
					if(player.GameLost()) //GameLost() checks if player has died.
					{
						mleft = false;
						level.ClearLevel();
						player.Reset();
						for(int g = 0; g<2; g++)
						{
							guard[g].Reset();
						}
						menu_pointer = -100;
						current_state = LOSE;
					}
				}
				else
				{
					MessageBox(ghwnd, "Game Paused", "", MB_ICONINFORMATION);
					paused = false;
				}
				
				//call drawsprite for all game elements - this will render everything on screen
				DrawSprite(floor);
				
				DrawAnimatedSprite(player.Star);
				
				DrawAnimatedSprite(player);
				
				for(int g = 0; g<numofguards; g++)
				{
					if(guard[g].Bullets.size()>0)
				{
					for(int b = 0; b<guard[g].Bullets.size(); b++)
					{
						guard[g].Bullets[b].SetDisplayBitmap("bullet.bmp");
						DrawAnimatedSprite(guard[g].Bullets[b]);
					}
				
				}
					DrawAnimatedSprite(guard[g]);
				}	
				//draw all the scenery
				for(int wall = 0; wall < level.Wall.size(); wall++) //draw all wall sprites
				{
					DrawSprite(level.Wall[wall]);
				}
				
				for(int key = 0; key < level.Key.size(); key++)	//draw key sprite

				{
					DrawAnimatedSprite(level.Key[key]);
				}
						
				for(int door = 0; door < level.Door.size(); door++)
				{
					DrawAnimatedSprite(level.Door[door]);
				}

				displayFrame();
			}
			break;
			
	//**********************************************PLAYER DIED SCREEN****************************************************//
		case LOSE:
		
			if(MousePos.y > 200 && MousePos.y < 250)
			{
				tryagain.Highlight();
				if(mleft)
				{
					mleft = false;
					current_state = MENU;
				}
			}
			else
			{
				tryagain.Unhighlight();
			}

			if(MousePos.y > 250 && MousePos.y < 300)
			{
				exit.Highlight();
				if(mleft)
				{
					mleft = false;
					lvl = 0;
					current_state = FRONT;
				}
			}
			else
			{
				exit.Unhighlight();
			}
			if(WaitFor(15))
			{
				DrawSprite(black);
				DrawSprite(died);
				DrawSprite(tryagain);
				DrawSprite(exit);
				displayFrame();
			}
			break;
			
	//****************************************PLAYER COMPLETED A LEVEL****************************************************//
		case WIN:
			
			if(MousePos.y > 200 && MousePos.y < 250)
			{
				nextlvl.Highlight();
				if(mleft)
				{
					mleft = false;
					lvl++;
					out.open("currentlevel.txt", ios::out | ios::trunc); //create file called currentlevel.txt for output only
					out << lvl << endl; //write lvl variable to file
					out.close(); //close file
					current_state = MENU;
				}
			}
			else
			{
				nextlvl.Unhighlight();
			}

			if(MousePos.y > 250 && MousePos.y < 300)
			{
				exit.Highlight();
				if(mleft)
				{
					mleft = false;
					lvl = 0;
					current_state = FRONT;
				}
			}
			else
			{
				exit.Unhighlight();
			}
			if(WaitFor(15))
			{
				DrawSprite(black);
				DrawSprite(lvlcomp);
				DrawSprite(nextlvl);
				DrawSprite(exit);
				displayFrame();
			}
			break;
			
			//****************************************PLAYER COMPLETED GAME**********************************************************//
		case COMPLETE:
					
			if(mleft)
			{
				mleft = false;
				lvl = 0;
				out.open("currentlevel.txt", ios::out | ios::trunc); //create file called currentlevel.txt for output only
				out << lvl << endl; //write lvl variable to file
				out.close(); //close file 
				current_state = FRONT;
			}
		
			if(WaitFor(15))
			{
				DrawSprite(black);
				DrawSprite(congrats);
				displayFrame();
			}
			break;
	}
}

void Stealth::DrawSprite(WinSprite theSprite)
{
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, theSprite.bitmap);
	BitBlt(backHDC, theSprite.GetX(), theSprite.GetY(), theSprite.GetWidth(), 
		theSprite.GetHeight(),bitmapHDC,0,0,SRCCOPY);
	SelectObject(bitmapHDC,originalBitMap); 
}

void Stealth::DrawAnimatedSprite(WinSprite theSprite)
{
	HBITMAP originalBitMap;
	originalBitMap = (HBITMAP)SelectObject(bitmapHDC, theSprite.bitmap);
	PlgBlt(backHDC, theSprite.GetPoints(), bitmapHDC, 0, 0, theSprite.GetWidth(),
		theSprite.GetHeight(), theSprite.bitmask, 0, 0);
	SelectObject(bitmapHDC,originalBitMap); 
}

//FUNCTIONS///
//the RegisterMyWindow functionc creates and registers an instance of the Windows class
void RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX  wcex;									

    wcex.cbSize        = sizeof (wcex);				
    wcex.style         = CS_HREDRAW | CS_VREDRAW;		
    wcex.lpfnWndProc   = WndProc;						
    wcex.cbClsExtra    = 0;								
    wcex.cbWndExtra    = 0;								
    wcex.hInstance     = hInstance;						
    wcex.hIcon         = 0; 
    wcex.hCursor       = LoadCursor (NULL, IDC_ARROW);	
															
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wcex.lpszMenuName  = NULL;							
    wcex.lpszClassName = "FirstWindowClass";				
    wcex.hIconSm       = 0; 

	RegisterClassEx (&wcex);							
}

//this function initialises the current instance of the windows class and opens a window
BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	HWND        hwnd;
	hwnd = CreateWindow ("FirstWindowClass",					
						 "Stealth",		  	
						 WS_OVERLAPPEDWINDOW,	
						 CW_USEDEFAULT,			
						 CW_USEDEFAULT,			
						 SCREENWIDTH,			
						 SCREENHEIGHT,			
						 NULL,					
						 NULL,					
						 hInstance,				
						 NULL);								
	if (!hwnd)
	{
		return FALSE;
	}

    ShowWindow (hwnd, nCmdShow);  //opens the window						
    UpdateWindow (hwnd);	
	ghwnd = hwnd;
	return TRUE;

}



BOOL WaitFor(unsigned long delay)
{
	static unsigned long clockStart = 0;
	unsigned long timePassed;
	unsigned long now = timeGetTime();

	timePassed = now - clockStart;
	if (timePassed >  delay)
	{
		clockStart = now;
		return TRUE;
	}
	else
		return FALSE;
}
	
			
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)											
    {														
		case WM_CREATE:	
			break;

		case WM_SIZE:
			break;	

		case WM_KEYDOWN:
			keys[wParam]=true;
			break;

		case WM_KEYUP:
			keys[wParam]=false;
			break;

		case WM_MOUSEMOVE:
			MousePos.x = LOWORD (lParam);
			MousePos.y = HIWORD (lParam);
			break;

		case WM_LBUTTONDOWN:
			mleft  = true;
			mright = false;
			mmiddle = false;
			break;
			
		case WM_RBUTTONDOWN:
			mright = true;
			mleft  = false;
			mmiddle = false;
			break;

		case WM_MBUTTONDOWN:
			mmiddle = true;
			mleft  = false;
			mright = false;
			break;

		case WM_PAINT:
			
	
		    break;		

		case WM_DESTROY:	
			
			PostQuitMessage(0);	
								
			break;				
	}													

	return DefWindowProc (hwnd, message, wParam, lParam);		
															
}

void setBuffers()
{
	GetClientRect(ghwnd, &screenRect);	//creates rect based on window client area
	frontHDC = GetDC(ghwnd);			// Initialises front buffer device context (window)
	backHDC = CreateCompatibleDC(frontHDC);// sets up Back DC to be compatible with the front
	bitmapHDC=CreateCompatibleDC(backHDC);
	theOldFrontBitMap = CreateCompatibleBitmap(frontHDC, screenRect.right, 
		screenRect.bottom);		//creates bitmap compatible with the front buffer
    theOldBackBitMap = (HBITMAP)SelectObject(backHDC, theOldFrontBitMap);
								//creates bitmap compatible with the back buffer
	FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

//double buffering function
void displayFrame() //copy back buffer to the front (displayed) buffer
{
		BitBlt(frontHDC, screenRect.left, screenRect.top, screenRect.right, 
		screenRect.bottom, backHDC, 0, 0, SRCCOPY);
		FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void releaseResources()
{
	SelectObject(backHDC,theOldBackBitMap);
	DeleteDC(backHDC);
	DeleteDC(bitmapHDC);
	ReleaseDC(ghwnd,frontHDC);
}


