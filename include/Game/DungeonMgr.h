#pragma once
#include <Backend/Types.h>

#include "Game/Dungeons/Dungeon.h"


namespace PKMD::Game
{
	class DungeonMgr
	{
	public:
		static DungeonMgr* GetInstance();
		static DungeonMgr* CreateInstance();
		static void DestroyInstance();

		void Init();

		bool RegisterNewDungeon(const std::string& id, const Dungeon::Dungeon* dungeon);
		Dungeon::Dungeon* GetCurrDungeon();

	private:
		Dungeon::Dungeon* currDungeon;
		Dungeon::Dungeon* nextDungeon;

		std::map<const std::string, const Dungeon::Dungeon*> dungeonMap;
	};
};