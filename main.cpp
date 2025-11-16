#include "Game/GameManager.h"
#include <filesystem>
#include <stdio.h>

// Should ideally make a logger at some point
using namespace PKMD::Game;

int main()
{
	GameManager::Create();

	GameManager* gameMgr = GameManager::Instance();
	std::filesystem::path cwd = std::filesystem::current_path();
	std::cout << "Current System Path: " << cwd << "\n";

	
	PKMD_ASSERT(gameMgr);

	PKMD_ASSERT(gameMgr->LoadAssets());

	return 0;
}