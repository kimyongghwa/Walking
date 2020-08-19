#pragma once
#include "Object.h"
#include "Animation.h"
class Eneme : public Object
{
private:
	Animation* enemeAnimation;
	float gravity;
	bool doubleJump, isJump;

public:
	Eneme();
	~Eneme();

	void Render();
	void Update(float dTime);

};

