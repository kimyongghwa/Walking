#include "stdafx.h"
#include "Eneme.h"

Eneme::Eneme() {
	isJump = false;
	doubleJump = false;
	gravity = 9.8;

	enemeAnimation = new Animation(10);
	enemeAnimation->AddFrame("Resources/Image/gazeman0.png");
	enemeAnimation->AddFrame("Resources/Image/gazeman1.png");
	enemeAnimation->AddFrame("Resources/Image/gazeman2.png");
	AddChild(enemeAnimation);

	rect = enemeAnimation->getRect();
}
Eneme::~Eneme() {

}

void Eneme::Render() {
	Object::Render();
	enemeAnimation->Render();
}

void Eneme::Update(float dTime) {
	gravity += 9.8f;

	setPos(getPosX(), getPosY() + gravity * dTime);
	if (inputManager->GetKeyState(VK_RIGHT) == KEY_ON) {
		setPos(getPosX() + 300 * dTime, getPosY());
	}
	if (inputManager->GetKeyState(VK_LEFT) == KEY_ON) {
		setPos(getPosX() - 300 * dTime, getPosY());
	}
	if (isJump) {
		setPos(getPosX(), getPosY() - 300 * dTime);
	}
	if (getPosY() > 410) {
		setPos(getPosX(), 410);
		isJump = false;
	}

	if (inputManager->GetKeyState(VK_UP) == KEY_DOWN) {
		if (getPosY() > 50) {
			isJump = true;
			gravity = 0;
		}
	}
		enemeAnimation->Update(dTime);
}