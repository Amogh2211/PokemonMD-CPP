#include "Game/Dungeons/Dungeon.h"
#include <Backend/Utils/HashHelper.h>

namespace PKMD::Game::Dungeons
{
	Dungeon::Dungeon(const std::string& name)
	{
		PKMD_ASSERT(name.length() > 0); 

		m_dungeonParams.m_Name = name;
		m_dungeonParams.m_Id = PKMD::Backend::Utils::generateHash(m_dungeonParams.m_Name);
	}
	Dungeon::Dungeon(const Dungeon& other)
	{
		//PKMD_ASSERT()
	}
	size_t Dungeon::GetID() const
	{
		return m_dungeonParams.m_Id;
	}

	const std::string& Dungeon::GetName() const
	{
		return m_dungeonParams.m_Name;
	}
	
}
