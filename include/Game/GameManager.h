#pragma once
#include <Backend/Types.h>	


namespace PKMD::Game
{
	class GameManager : public Singleton<GameManager>
	{
	public:
		void Reset();
		bool LoadAssets();

	private:
		bool LoadAssetFiles();
		bool LoadDungeonsFromJson();

		struct AssetFilePaths
		{
			std::string& dungeonFilePath;
			//std::string& 
		};
		
		AssetFilePaths* m_assetFilePaths;

	};
}