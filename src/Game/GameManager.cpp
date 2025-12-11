#include "Backend/Types.h"
#include <Backend/ServiceMgr.h>
#include <Backend/Utils/FileUtils.h>


#include "Game/GameManager.h"
#include "Game/DungeonService.h"
#include <Game/GameManagerDefines.h>

using namespace PKMD::Backend::Utils;

namespace PKMD::Game
{
	void GameManager::Reset()
	{

	}

	void GameManager::Update()
	{
	}

	bool GameAssetManager::LoadAssets()
	{

		LoadAssetFiles();


		LoadDungeonsFromJson();
		
		return true;
	}

	void GameAssetManager::ParseAssets()
	{
	}

	bool GameAssetManager::LoadAssetFiles()
	{
		// Gather all file paths
		FilePathsParser* filePathsParser = new FilePathsParser();
		filePathsParser->DeserializeFromFile(filePathsJson);
		auto rootFilesMap = filePathsParser->getRootMap();

		// Parse dungeons
		std::string dungeonsFilePath = rootFilesMap["DungeonsFilePath"].asString();
		DungeonParser* dungeonParser = new DungeonParser();
		dungeonParser->DeserializeFromFile(dungeonsFilePath);
		m_assetJsonMaps.dungeonJsonMap = dungeonParser->getRootMap();

		
		
		// Clean up the allocations
		{
			delete dungeonParser;
			delete filePathsParser;
		}
		
		return true;
	}

	bool GameAssetManager::LoadDungeonsFromJson()
	{
		PKMD::Backend::ServiceMgr serviceMgr = PKMD::Backend::ServiceMgr::GetInstance();
		PKMD::Game::IDungeonRegistrar* dungeonRegistrar = static_cast<PKMD::Game::IDungeonRegistrar*>(serviceMgr.ProvideInterface<PKMD::Game::IDungeonRegistrar>());
		PKMD_ASSERT(dungeonRegistrar);
		
		PKMD_ASSERT(m_assetJsonMaps.dungeonJsonMap.size() > 0);

		const auto& dungeonMap = m_assetJsonMaps.dungeonJsonMap;
		for (const auto& dungeonName : dungeonMap.getMemberNames())
		{
			const auto& temp = dungeonMap[dungeonName];
			PKMD_ASSERT(dungeonRegistrar->RegisterNewDungeonData(dungeonName, temp));
		}
		
		
		return false;
	}
}
