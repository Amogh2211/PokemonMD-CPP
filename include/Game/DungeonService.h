#pragma once
#include <Backend/Types.h>
#include <Backend/Utils/Parser.h>

#include "Game/Dungeons/Dungeon.h"

using namespace PKMD::Game::Dungeons;
namespace PKMD::Game
{
	struct IDungeonRegistrar
	{
		virtual bool RegisterNewDungeon(const std::string& id, const Dungeon* dungeon) = 0;
		PKMD_SERVICE_INTERFACE;
	};

	class DungeonParser : public PKMD::Backend::Utils::IJsonParser
	{
	public:
		virtual bool Deserialize(const std::string& jsonText) override;
		// Deserialize JSON from an input stream
		virtual bool Deserialize(std::istream& input) override;
		// Deserialize JSON from a file
		virtual bool DeserializeFromFile(const std::string& filePath) override;
		
		virtual Json::Value getRootMap() const override { return m_rootMap;  };
	private:
		bool ParseDungeons() const;
		Json::Value m_rootMap;
	};
	
};