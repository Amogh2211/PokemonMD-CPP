#pragma once
#include <Backend/Types.h>
#include <Game/BaseTypes/GameObject.h>


namespace PKMD::Game::Dungeons
{
	
	class Dungeon : public PKMD::Game::GameObject
	{
	public:
		Dungeon(const std::string& name);
		Dungeon(const Dungeon&);
		
		size_t GetID() const; 
		const std::string& GetName() const;

		// Fill floor data

	private:
		Dungeon() = default;

		//EnemyPools enemyPools;
		//std::vector<Floor*> floors;
		//DungeonParams m_dungeonParams;
	};
}