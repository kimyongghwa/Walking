#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() {
	pscore = 0;
	score = 0;
	coinCounter = 0;

	backgroundInstatiate = false;
	bridgeInstantiate = false;
	obstacleInstantiate = true;

	obstacleInstDelayTimer = 0;
	coinInstDelayTimer = 0;
	result = new Background("Resources/Image/Untitled.png");
	Background* background = new Background();
	background->setPos(0, 0);
	backgroundList.push_back(background);
	AddObject(background);

	//Bridge* bridge = new Bridge();
	//bridge->setPos(0, 500);
	//bridgeList.push_back(bridge);
	//AddObject(bridge);	

	for (int i = 0; i < 2; i++) {
		numArray[i] = new Number();
		numArray[i]->setPos(0 + 60 * i, 10);
		AddUI(numArray[i]);
	}
	for (int i = 0; i < 2; i++) {
		pnumArray[i] = new Number();
		pnumArray[i]->setPos(500 + 60 * i, 10);
		AddUI(pnumArray[i]);
	}
	eneme = new Eneme();
	eneme->setPos(700, 0);
	player = new Player();
	AddObject(player);
	
}

GameScene::~GameScene() {

}

void GameScene::Render() {
	for (auto& background : backgroundList) {
		background->Render();
	}
	//for (auto& bridge : bridgeList) {
	//	bridge->Render();
	//}
	for (auto& obstacle : obstacleList) {
		obstacle->Render();
	}
	//for (auto& coin : coinList) {
	//	coin->Render();
	//}
	for (auto& bullet : bulletList) {
		bullet->Render();
	}
	player->Render();
	eneme->Render();
	for (int i = 0; i < 2; i++) {
		numArray[i]->Render();
	}
	for (int i = 0; i < 2; i++) {
		pnumArray[i]->Render();
	}
	result->Render();
}

void GameScene::Update(float dTime) {
	Scene::Update(dTime);
	eneme->Update(dTime);
	UISetting();
	TimerSetting(dTime);
	OptimizationObject();
	InstantiateObject();
	CollisionCheck();
	for (auto& bullet : bulletList) {
		bullet->Update(dTime);
	}
	if (inputManager->GetKeyState('S') == KEY_DOWN) {
		if (player->getPosX() < eneme->getPosX()) {

			bulletList.push_back(new Bullet(player->getPos(), true, true));
		}
		else {
			bulletList.push_back(new Bullet(player->getPos(), false, true));
		}
	}
	if (inputManager->GetKeyState(VK_DOWN) == KEY_DOWN) {
		if (player->getPosX() > eneme->getPosX())
		{
			std::cout << eneme->getPosX() <<std::endl;
			bulletList.push_back(new Bullet(eneme->getPos(), true, false));
		}
		else
		{
			std::cout << eneme->getPosX() << std::endl;
			bulletList.push_back(new Bullet(eneme->getPos(), false, false));
		}
	}
	
}

void GameScene::TimerSetting(float dTime) {
	coinInstDelayTimer += dTime;
	obstacleInstDelayTimer += dTime;
}

void GameScene::UISetting() {
	numArray[0]->setNum(score / 10);
	numArray[1]->setNum(score % 10);
	pnumArray[0]->setNum(pscore / 10);
	pnumArray[1]->setNum(pscore % 10);
}

void GameScene::OptimizationObject() {
	//for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
	//	if ((*iter)->getPosX() < -SCREEN_WIDTH) {
	//		RemoveObject((*iter));
	//		SAFE_DELETE(*iter);
	//		iter = backgroundList.erase(iter);
	//		backgroundInstatiate = false;
	//		obstacleInstantiate = false;
	//		if (iter == backgroundList.end()) {
	//			break;
	//		}
	//	}
	//}


	//for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {
	//	if ((*iter)->getPosX() < -SCREEN_WIDTH) {
	//		RemoveObject((*iter));
	//		SAFE_DELETE(*iter);
	//		iter = bridgeList.erase(iter);
	//		bridgeInstantiate = false;
	//		if (iter == bridgeList.end()) {
	//			break;
	//		}
	//	}
	//}

	/*for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);
			if (iter == coinList.end()) {
				break;
			}
		}
	}*/

	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++) {
		if ((*iter)->getPosX() < -SCREEN_WIDTH) {
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = obstacleList.erase(iter);

			if (iter == obstacleList.end()) {
				break;

			}
		}
	}
}

void GameScene::CollisionCheck() {
	for (auto iter = bulletList.begin(); iter != bulletList.end(); iter++) {
		if (player->IsCollisionRect((*iter))) {
			if (!(*iter)->PlayerCheck())
			{
				pscore += 1;
				RemoveObject((*iter));
				SAFE_DELETE(*iter);
				iter = bulletList.erase(iter);
				if (pscore == 20)
					result = new Background("Resources/Image/lose.png");
				pscore %= 100;
			}
			if (iter == bulletList.end()) {
				break;
			}
		}
		if (eneme->IsCollisionRect((*iter))) {
			if ((*iter)->PlayerCheck())
			{
				score += 1;
				RemoveObject((*iter));
				SAFE_DELETE(*iter);
				iter = bulletList.erase(iter);
				if (score == 20)
					result = new Background("Resources/Image/win.png");
				score %= 100;

			}
			if (iter == bulletList.end()) {
				break;
			}
		}

	}

	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++) {
		if (player->IsCollisionRect((*iter))) {
			sceneManager->ChangeScene(new MainScene());
			return;
		}
	}
}

void GameScene::InstantiateObject() {
	//if (!backgroundInstatiate) {
	//	Background* background = new Background();
	//	background->setPos(SCREEN_WIDTH - 20, 0);
	//	backgroundList.push_back(background);
	//	AddObject(background);
	//	backgroundInstatiate = true;
	//}

	//if (!bridgeInstantiate) {
	//	Bridge* bridge = new Bridge();
	//	bridge->setPos(SCREEN_WIDTH - 20, 500);
	//	bridgeList.push_back(bridge);
	//	AddObject(bridge);
	//	bridgeInstantiate = true;
	//}

	if (!obstacleInstantiate) {
		if (obstacleInstDelayTimer > 1.f) {
			obstacleInstDelayTimer = 0;
			coinCounter = 4;
			Obstacle* obstacle = new Obstacle(rand() % 2);
			obstacle->setPos(SCREEN_WIDTH + 50, 400);
			AddObject(obstacle);
			obstacleList.push_back(obstacle);
			obstacleInstantiate = true;
		}
	}

	//if (coinCounter > 0) {
	//	if (coinInstDelayTimer > 0.1f) {
	//		coinCounter--;
	//		coinInstDelayTimer = 0;
	//		Coin* coin = new Coin(true);
	//		coin->setPos(SCREEN_WIDTH, 300);
	//		AddObject(coin);
	//		coinList.push_back(coin);
	//	}
	//}
	//else {
	//	if (coinInstDelayTimer > 0.1f) {
	//		coinInstDelayTimer = 0;
	//		Coin* coin = new Coin(false);
	//		coin->setPos(SCREEN_WIDTH, 400);
	//		AddObject(coin);
	//		coinList.push_back(coin);
	//	}
	//}
}