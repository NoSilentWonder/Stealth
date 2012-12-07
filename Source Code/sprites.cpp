#include "sprites.h"


WinSprite::WinSprite()
{
	PI = 3.14159265359;
	m_x = m_y = 0;

	m_Vx = m_Vy = 1;
	m_w = m_h = 32;

	m_cx = m_x + m_w*0.5;
	m_cy = m_y + m_h*0.5;

	bitmask = NULL;

	/*Points[0].x = m_x;
	Points[0].y = m_y;
	Points[1].x = m_x + m_w;
	Points[1].y = m_y;
	Points[2].x = m_x + m_w;
	Points[2].y = m_y + m_h;
	Points[3].x = m_x;
	Points[3].x = m_y + m_h;*/

	Initialise();

	CalculateVariables();
}

WinSprite::~WinSprite()
{
	// Nothing to clean-up
}

void WinSprite::Initialise(void)
{
	m_z = 0;
	
	m_rota = 0.0f;

	CalculateVariables();
}

void WinSprite::CalculateVariables(void)
{	
	int hWidth = m_w*0.5;
	int hHeight = m_h*0.5;

	m_cx = m_x + m_w*0.5;
	m_cy = m_y + m_h*0.5;

	m_radius = sqrt((float)((hHeight*hHeight) + (hWidth*hWidth)));

	float anglerads = (m_rota*PI)/180;

	float cosine  = cos(anglerads);
	float sine    = sin(anglerads);
	float hcosine = cos(anglerads + PI*0.5);
	float hsine   = sin(anglerads + PI*0.5);

	Points[0].x  = (int)(cosine  * hWidth);
	Points[0].y  = (int)(sine    * hWidth);
	Points[1].x  = (int)(hcosine * hHeight);
	Points[1].y  = (int)(hsine   * hHeight);

	//points on parallelogram
	Points[2].x  = (int)(hWidth  + m_x - Points[0].x - Points[1].x);
	Points[2].y  = (int)(hHeight + m_y - Points[0].y - Points[1].y);
	Points[3].x  = (int)(hWidth  + m_x - Points[1].x + Points[0].x);
	Points[3].y  = (int)(hHeight + m_y - Points[1].y + Points[0].y);
	Points[4].x  = (int)(hWidth  + m_x - Points[0].x + Points[1].x);
	Points[4].y  = (int)(hHeight + m_y - Points[0].y + Points[1].y);
	//Points[5].x  = (int)(hWidth  + m_x + Points[0].x + Points[1].x);
	//Points[5].y  = (int)(hHeight + m_y + Points[0].y + Points[1].y);
	
	grid_a = (int)((m_x+m_w*0.5)/32);
	grid_b = (int)((m_y+m_h*0.5)/32);
}

void WinSprite::MoveTo(const int x, const int y)
{
	m_px = m_x;
	m_py = m_y;
	m_x = x;
	m_y = y;

	CalculateVariables();
}
	
void WinSprite::MoveDeltaX(const int x)
{
	m_px = m_x;
	m_x += x;
	CalculateVariables();
}
	
void WinSprite::MoveDeltaY(const int y)
{
	m_py = m_y;
	m_y += y;
	CalculateVariables();
}

void WinSprite::SetVelocity(const int Vx, const int Vy)
{
	m_Vx = Vx;
	m_Vy = Vy;
}

void WinSprite::SetDimensions(const int w, const int h)
{
	m_w = w;
	m_h = h;
	CalculateVariables();
}

void WinSprite::SetRotation(const float r)
{
	m_rota = r;
	CalculateVariables();
}
	
void WinSprite::Move(void)
{
	// Update coordinates using the velocity vector components.
	MoveDeltaX(m_Vx);
	MoveDeltaY(m_Vy);
	CalculateVariables();
}

void WinSprite::Rotate(const float r)
{
	m_rota += r;
	while((m_rota>360) || (m_rota<0))
	{
		m_rota -= m_rota > 360 ? 360 : 0;
		m_rota += m_rota < 0 ? 360 : 0; 
	}
	CalculateVariables();
}

void WinSprite::IncreaseVelocityX(const int Vx)
{
	m_Vx += Vx;
}
	
void WinSprite::IncreaseVelocityY(const int Vy)
{
	m_Vy += Vy;
}

void WinSprite::SetDisplayBitmap(LPSTR szFileName)
{
	bitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void WinSprite::SetDisplayBitmask(LPSTR szFileName)
{
	bitmask = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}