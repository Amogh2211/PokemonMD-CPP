#pragma once
#include <vector>
#include "Game/AI/Enemy.h"


namespace PKMD::Game
{
	class Floor
	{
	private:
		std::vector<PKMD::Game::Enemy*> enemies;
	};
}