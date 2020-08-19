#pragma once
#include "Object.h"
#include "Animation.h"
#include "Bullet.h"

class Player : public Object
{
private :
	
	float gravity;
	bool doubleJump, isJump;

public :
	Animation* playerAnimation;
	Player();
	~Player();

	void Render();
	void Update(float dTime);

};