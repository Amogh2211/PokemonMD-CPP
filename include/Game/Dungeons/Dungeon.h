#pragma once
#include <Backend/Types.h>

namespace PKMD::Game::Dungeons
{
	typedef int FloorNum;
	typedef std::map<FloorNum, std::vector<std::string>> EnemyPools;

	class Floor;

	class Dungeon
	{
	public:
		Dungeon(const std::string& name);
		Dungeon(const Dungeon&);
		
		size_t GetID() const; 
		const std::string& GetName() const;

		struct DungeonParams
		{
			std::string m_Name = "";
			size_t m_Id = 0;
			size_t m_NumLevels = 0;
		};

	private:
		Dungeon() = default;

		EnemyPools enemyPools;
		std::vector<Floor*> floors;
		DungeonParams m_dungeonParams;
	};
}