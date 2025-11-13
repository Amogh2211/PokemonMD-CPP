#include "Game/GameManager.h"


int main()
{
	PKMD::Game::GameManager* gameManager = PKMD::Game::GameManager::GetInstance();
	gameManager->Init();

	return 0;
}