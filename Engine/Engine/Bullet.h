#pragma once
#include "Sprite.h"
#include "Player.h"
#include "Eneme.h"
#include "Object.h"
class Bullet : public Object
{
private:
	Sprite* bullet;
	bool isPlayer;
	bool isRight;
public:
	Bullet(D3DXVECTOR2 vector, bool isRight, bool isPlayer);
	~Bullet();
	bool PlayerCheck();
	void Render();
	void Update(float dTime);
};

