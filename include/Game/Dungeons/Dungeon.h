#pragma once
#include <Backend/Types.h>
#include <Game/Dungeons/Floor.h>


namespace PKMD::Game::Dungeon
{
	typedef int FloorNum;
	typedef std::map<FloorNum, std::vector<std::string>> EnemyPools;
	class Dungeon
	{
		std::string m_Name = "";
		EnemyPools enemyPools;
		std::vector<PKMD::Game::Floor*> floors;
	};
}