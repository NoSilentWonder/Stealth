#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>

#pragma comment(lib, "winmm.lib")

class WinSprite 
{
public:

	WinSprite::WinSprite();

	WinSprite::~WinSprite();
	
	void MoveTo(const int x, const int y);
	
	void MoveDeltaX(const int x);
	
	void MoveDeltaY(const int y);
	
	void SetVelocity(const int Vx, const int Vy);

	void SetDimensions(const int w, const int h);

	void SetRotation(const float r);

	void Move(void);

	void Rotate(const float r);
	
	void IncreaseVelocityX(const int Vx);

	void IncreaseVelocityY(const int Vy);
	
	int GetX(void){return m_x;}
	
	int GetY(void){return m_y;}

	POINT * GetPoints(void){return & Points[2];}

	int GetPrevX(void){return m_px;}

	int GetPrevY(void){return m_py;}

	int GetCentreX(void){return m_cx;}

	int GetCentreY(void){return m_cy;}
	
	int GetWidth(void){return m_w;}
	
	int GetHeight(void){return m_h;}

	int GetVX(void){return m_Vx;}

	int GetVY(void){return m_Vy;}

	int GetGrid_a(void){return grid_a;}

	int GetGrid_b(void){return grid_b;}

	float GetRotation(void){return m_rota;}

	int GetRadius(void){return m_radius;}

	void SetDisplayBitmap(LPSTR szFileName);

	void SetDisplayBitmask(LPSTR szFileName);

	HBITMAP bitmap;

	HBITMAP bitmask;

protected:

	void Initialise(void); //Initialise variables

	void CalculateVariables(void); 

	int m_x, m_y;	//position on screen
	int m_px, m_py; //previous x and y positions
	int m_cx, m_cy; //centre coordinates
	int m_z; //z depth (big = near)
	int m_w, m_h;	//width and height
	int m_Vx, m_Vy; //velocity vector components
	int grid_a, grid_b; //grid position
	float m_rota; //angle of rotation (degrees)
	int m_radius; //radius
	float PI;
	
	POINT Points[5];
};


#endif