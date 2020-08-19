#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(D3DXVECTOR2 vector, bool isRight, bool isPlayer) {
	this->isPlayer = isPlayer;
	this->isRight = isRight;
	if(isPlayer)
		bullet = new Sprite("Resources/Image/Shot.png");
	else
		bullet = new Sprite("Resources/Image/Crab.png");
	if(isPlayer)
		setPos(vector.x, vector.y+100);
	else
		setPos(vector.x, vector.y + 150);
	AddChild(bullet);
	if (!isRight)
		bullet->setScale(-1, 1);
	rect = bullet->getRect();
}

Bullet::~Bullet(){
}

bool Bullet::PlayerCheck()
{
	return isPlayer;
}

void Bullet::Update(float dTime) {
	Object::Update(dTime);
	if(isRight)
		setPos(getPosX() + 600 * dTime, getPosY());
	else
		setPos(getPosX() - 600 * dTime, getPosY());

}

void Bullet::Render() {
	Object::Render();
	bullet->Render();
}