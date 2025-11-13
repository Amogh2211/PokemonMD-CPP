#pragma once


namespace PKMD::Game
{
	class Pokemon
	{


	private:
		typedef struct stats_t
		{
			float m_health;
			float m_attack;
			float m_defense;
			float m_travelSpeed = 1;
		} Stats;
	};
}