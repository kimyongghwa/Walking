#include "stdafx.h"
#include "Player.h"

Player::Player() {
	isJump = false;
	doubleJump = false;
	gravity = 9.8f;

	playerAnimation = new Animation(10);
	playerAnimation->AddFrame("Resources/Image/Hero0.png");
	playerAnimation->AddFrame("Resources/Image/Hero1.png");
	playerAnimation->AddFrame("Resources/Image/Hero2.png");
	AddChild(playerAnimation);

	rect = playerAnimation->getRect();
}

Player::~Player() {

}

void Player::Render() {
	Object::Render();
	playerAnimation->Render();
}

void Player::Update(float dTime) {
	gravity += 9.8f;

	setPos(getPosX(), getPosY() + gravity * dTime);
	if (inputManager->GetKeyState('D') == KEY_ON) {
		setPos(getPosX() + 300 * dTime, getPosY());
	}
	if (inputManager->GetKeyState('A') == KEY_ON) {
		setPos(getPosX() - 300 * dTime, getPosY());
	}
	if (isJump) {
		setPos(getPosX(), getPosY() - 300 * dTime);
	}
	if (getPosY() > 480) {
		setPos(getPosX(), 480);

	}

	if (inputManager->GetKeyState('W') == KEY_DOWN) {
		if (getPosY() > 50) {
			isJump = true;
			gravity = 0;
		}
	}


	playerAnimation->Update(dTime);
}