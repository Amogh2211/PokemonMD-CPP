#include "Game/Dungeons/Dungeon.h"
#include <Backend/Utils/HashHelper.h>



static std::string stringTemp = "";
namespace PKMD::Game::Dungeons
{
	Dungeon::Dungeon(const std::string& name)
	{
		PKMD_ASSERT(name.length() > 0); 

		//m_dungeonParams.m_Name = name;
		//m_dungeonParams.m_Id = PKMD::Backend::Utils::generateHash(m_dungeonParams.m_Name);
	}
	Dungeon::Dungeon(const Dungeon& other)
	{
		PKMD_ASSERT(other.GetName().size() > 0);
		
		{
			//m_dungeonParams.m_Name = other.m_dungeonParams.m_Name;
			//m_dungeonParams.m_Id = other.m_dungeonParams.m_Id;
			//m_dungeonParams.m_NumFloors = other.m_dungeonParams.m_NumFloors;
		}
	}

	size_t Dungeon::GetID() const
	{
		return size_t();
		//return m_dungeonParams.m_Id;
	}

	const std::string& Dungeon::GetName() const
	{
		return stringTemp;
		//return m_dungeonParams.m_Name;
	}
	
}
