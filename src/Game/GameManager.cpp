#include "Backend/Types.h"


#include "Game/GameManager.h"
#include "Game/DungeonMgr.h"

namespace PKMD::Game
{
	static GameManager* g_GameManagerInstance = nullptr;

	GameManager* GameManager::Create()
	{
		PKMD_ASSERT(g_GameManagerInstance == nullptr);
		if (!g_GameManagerInstance)
			g_GameManagerInstance = new GameManager();

		return g_GameManagerInstance;
	}

	GameManager* Game::GameManager::GetInstance()
	{
		if (g_GameManagerInstance == nullptr)
		{
			g_GameManagerInstance = GameManager::Create();
		}
		return g_GameManagerInstance;
	}

	void Game::GameManager::Destroy()
	{
		PKMD_ASSERT(g_GameManagerInstance);
		delete g_GameManagerInstance;
	}

	void GameManager::Init()
	{
		DungeonMgr* dungeonMgr = PKMD::Game::DungeonMgr::GetInstance();
		dungeonMgr->Init();
	}

	void Game::GameManager::InitGameManager()
	{
	}

}
