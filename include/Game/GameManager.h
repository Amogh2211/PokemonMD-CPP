#pragma once
#include <Backend/Types.h>	
#include <json/json.h>

namespace PKMD::Game
{
	class GameManager : public Singleton<GameManager>
	{
	public:
		void Reset();
		bool LoadAssets();

	private:
		void ParseAssets();
		bool LoadAssetFiles();
		bool LoadDungeonsFromJson();

		struct AssetJsonMaps
		{
			Json::Value dungeonJsonMap;
			
		};
		
		AssetJsonMaps m_assetJsonMaps;

	};
}