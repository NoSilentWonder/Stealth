#ifndef _TEXTSPRITES_H_
#define _TEXTSPRITES_H_

#include "sprites.h"

//TEXTSPRITES CLASS INHERITED FROM WINSPRITES
//THIS CLASS ADDS THE FEATURE OF BITMAP TOGGLING FOR WHEN TEXT IS BEING HIGHLIGHTED
class TextSprite: public WinSprite 
{
public:
	TextSprite(void); //constructor

	void Highlight(void); //toggle textsprite to show highlighted bitmap

	void Unhighlight(void); //toggle trextsprite to show normal bitmap

	bool IsHighlighted(void); //returns hightlighted boolean

	void LoadBitMaps(LPSTR normal, LPSTR highlighted); //stores the bitmaps for text sprites

private:
	HBITMAP textbitmaps[2];

	bool highlighted;
};


#endif