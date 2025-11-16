#include "Game/DungeonService.h"
#include "Backend/Types.h"
#include <Backend/Utils/FileUtils.h>
#include <string>
#include <filesystem>

namespace PKMD::Game
{
    class DungeonMgr : IDungeonRegistrar
    {
        PKMD_SERVICE_BIND1(DungeonMgr, IDungeonRegistrar);

        bool RegisterNewDungeon(const std::string& id, std::unique_ptr<Dungeon> dungeon) override;

        Dungeon* GetCurrDungeon();

    private:
        Dungeon* currDungeon = nullptr;
        Dungeon* nextDungeon = nullptr;

        std::map<const std::string, std::unique_ptr<Dungeon>> dungeonMap;
    };

    bool DungeonMgr::RegisterNewDungeon(const std::string& id, std::unique_ptr<Dungeon> dungeon)
    {
        if (dungeonMap.find(id) != dungeonMap.end())
        {
            dungeonMap[id] = std::move(dungeon);
            return true;
        }
        return false;
    }

    Dungeon* DungeonMgr::GetCurrDungeon()
    {
        PKMD_ASSERT(currDungeon);
        return currDungeon;
    }

	// --------------- Parser -----------------------


	bool DungeonParser::Deserialize(const std::string& jsonText)
	{
		return false;
	}

	bool DungeonParser::Deserialize(std::istream& input)
	{
		// Create a JsonCpp root value
		PKMD::Backend::Utils::populateRoot(input, m_rootMap);
		return true;
	}

	bool DungeonParser::DeserializeFromFile(const std::string& filePath)
	{
        
        std::ifstream fileStream(filePath); 
        CHECK_OPEN_FILE(fileStream);

		return Deserialize(fileStream);
	}

}
