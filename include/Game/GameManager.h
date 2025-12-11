#pragma once
#include <Backend/Types.h>	
#include <json/json.h>


namespace PKMD::Game
{
	class GameObject;
	class GameAssetManager : public Singleton<GameAssetManager, true>
	{
	public:
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

	class GameManager : public Singleton<GameManager, true>
	{
	public:
		void Reset();
		void InitGame() const
		{
			// Load assets
			GameAssetManager* gameAssetManager = GameAssetManager::Instance();
			PKMD_ASSERT(gameAssetManager->LoadAssets());
		};

		void Update();


	private:
		std::vector<GameObject*> m_registeredGameObjects;

	};

	
}