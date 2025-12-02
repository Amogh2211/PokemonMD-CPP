#include <Backend/Utils/FileUtils.h>
#include <Backend/Utils/HashHelper.h>
#include <Backend/Types.h>

#include "Game/DungeonService.h"
#include <Game/Dungeons/Dungeon.h>


#include <string>
#include <filesystem>

namespace PKMD::Game
{
	// Json Value Keys
	std::string dungeonMapKeys[] =
	{
		"Floors"
	};
	std::string floorMapKeys[] = 
	{
		"MinRooms",
		"MaxRooms",
		"Enemies",
		"Items",
		"Traps"
		"Weather",
		"Generator"
	};
	std::string enemyMapKeys[] =
	{
		"Species",
		"MinLevel",
		"MaxLevel",
		"Weight"
	};

	/// @brief Data related to each enemy that is to be spawned
	struct EnemyParams
	{
		std::string           mSpecies;
		std::pair<int, int>   mLevelRange;
		float                 mSpawnWeights;
	};
	using EnemyParamsVector = std::vector<EnemyParams>;
	/// @brief Floor based data
	struct FloorParams
	{
		std::pair<int, int>       mRoomRange;
		EnemyParamsVector         mEnemyParams;
	};

	typedef int FloorNum;
	typedef std::map<FloorNum, EnemyParamsVector> EnemyPools;

	
	struct DungeonParams
	{
		std::string m_Name = "";
		size_t m_Id = -1;
		size_t m_NumFloors = -1;
		size_t m_dificultyLevel = -1;
		std::vector<FloorParams> mFloorParams;
	};

    
    class DungeonMgr : IDungeonRegistrar, IDungeonCreator
    {
        PKMD_SERVICE_BIND2(DungeonMgr, IDungeonRegistrar, IDungeonCreator);

        virtual bool RegisterNewDungeonData(const std::string& id, const Json::Value& dungeon) override;
		virtual Dungeon* BuildAndRegisterDungeonFromParams(const std::string& dungeonName) override;

        Dungeon* GetCurrDungeon();
		void SetCurrentDungeon(const std::string& dungeonName);
    private:
		void BuildDungeonParams(DungeonParams&,const Json::Value&);

        Dungeon* currDungeon = nullptr;
        
		// dungeon name -> dungeon params
        std::map<const std::string, DungeonParams> m_dungeonDataMap;
		std::map < const std::string, Dungeon*> m_dungeonInstances;
    };

    bool DungeonMgr::RegisterNewDungeonData(const std::string& id, const Json::Value& dungeonParamsMap)
    {
        if (m_dungeonDataMap.find(id) == m_dungeonDataMap.end())
        {
			DungeonParams newDungeonParams;
			newDungeonParams.m_Name = id;
			newDungeonParams.m_Id = PKMD::Backend::Utils::generateHash(id);

			BuildDungeonParams(newDungeonParams, dungeonParamsMap);
            m_dungeonDataMap[id] = newDungeonParams;
            return true;
        }
        return false;
    }

	Dungeon* DungeonMgr::BuildAndRegisterDungeonFromParams(const std::string& dungeonName)
	{
		return nullptr;
	}

    Dungeon* DungeonMgr::GetCurrDungeon()
    {
        PKMD_ASSERT(currDungeon);
        return currDungeon;
    }

	void DungeonMgr::SetCurrentDungeon(const std::string& dungeonName)
	{
		if (m_dungeonInstances.find(dungeonName) != m_dungeonInstances.end())
		{
			currDungeon = m_dungeonInstances[dungeonName];
		}
		else
		{
			currDungeon = nullptr;
		}

#ifdef PKMD_DEBUG
		PKMD_INFO_ASSERT(currDungeon != nullptr,
			"Dungeon not found: %s",
			dungeonName.c_str());
#endif
	}

	void DungeonMgr::BuildDungeonParams(DungeonParams& outParams, const Json::Value& dungeonParamsMap)
	{
		
		const auto& floorData = dungeonParamsMap[dungeonMapKeys[0]];
		const int numFloors = floorData.size();
		outParams.m_NumFloors = numFloors;


		for (int i = 0; i < numFloors; ++i)
		{
			const auto& temp = floorData[i];
			FloorParams newFloorParams;
			newFloorParams.mRoomRange.first = temp[floorMapKeys[0]].asInt();
			newFloorParams.mRoomRange.second = temp[floorMapKeys[1]].asInt();

			const auto& enemyArray = temp[floorMapKeys[2]];
			const int enemyTypes = enemyArray.size();
			
			for (int i = 0; i < enemyTypes; ++i)
			{
				EnemyParams newEnemyParams;

				std::cout << "----------------------\n-------------------\n";
				newEnemyParams.mSpecies = enemyArray[i][enemyMapKeys[0]].asString();
				newEnemyParams.mLevelRange.first = enemyArray[i][enemyMapKeys[1]].asInt();
				newEnemyParams.mLevelRange.second = enemyArray[i][enemyMapKeys[2]].asInt();
				newEnemyParams.mSpawnWeights = enemyArray[i][enemyMapKeys[3]].asFloat();
				
				newFloorParams.mEnemyParams.push_back(newEnemyParams);
			}

			outParams.mFloorParams.push_back(newFloorParams);
		}
		
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
