#pragma once
#include "Object.h"
#include "Sprite.h"

class Background : public Object
{
private :
	Sprite* background;
public :
	Background();
	Background(const char* path);
	~Background();

	void Update(float dTime);
	void Render();
};