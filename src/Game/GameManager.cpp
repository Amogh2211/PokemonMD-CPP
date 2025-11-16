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
		PKMD_ASSERT(m_assetFilePaths);
		delete m_assetFilePaths;
	}

	bool GameManager::LoadAssets()
	{
		PKMD::Backend::ServiceMgr serviceMgr = PKMD::Backend::ServiceMgr::GetInstance();
	
		// Gather all file paths
		FilePathsParser* filePathsParser = new FilePathsParser();
		filePathsParser->DeserializeFromFile(filePathsJson);
		auto rootFilesMap = filePathsParser->getRootMap();

		// Parse dungeons
		std::string dungeonsFilePath = rootFilesMap["DungeonsFilePath"].asString();
		DungeonParser* dungeonParser = new DungeonParser();
		dungeonParser->DeserializeFromFile(dungeonsFilePath);

		return true;
	}
	
	bool GameManager::LoadAssetFiles()
	{

		return false;
	}

	bool GameManager::LoadDungeonsFromJson()
	{
		PKMD_ASSERT(m_assetFilePaths);
		

		return false;
	}
}
