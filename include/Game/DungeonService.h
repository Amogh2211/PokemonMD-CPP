#pragma once
#include <Backend/Types.h>
#include <Backend/Utils/Parser.h>


class Dungeon;
namespace PKMD::Game
{
	struct IDungeonRegistrar
	{
		virtual bool RegisterNewDungeonData(const std::string& id, const Json::Value& dungeon) = 0;
		PKMD_SERVICE_INTERFACE;
	};


	struct IDungeonCreator
	{
		virtual Dungeon* BuildAndRegisterDungeonFromParams(const std::string& dungeonName) = 0;
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
		Json::Value m_rootMap;
	};
	
};