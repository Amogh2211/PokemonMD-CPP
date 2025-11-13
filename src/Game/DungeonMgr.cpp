#include "Game/DungeonMgr.h"
#include "Backend/Types.h"
#include <string>


namespace PKMD::Game
{
    static DungeonMgr* g_DungeonManager = nullptr;
    
    
    DungeonMgr* DungeonMgr::GetInstance()
    {
        if (g_DungeonManager == nullptr)
        {
            g_DungeonManager = DungeonMgr::CreateInstance();
        }
        return g_DungeonManager;
    }

    DungeonMgr* DungeonMgr::CreateInstance()
    {
        PKMD_ASSERT(g_DungeonManager == nullptr);
        if (g_DungeonManager == nullptr)
        {
            g_DungeonManager = new DungeonMgr();
        }
        return g_DungeonManager;
    }

    void DungeonMgr::DestroyInstance()
    {
        PKMD_ASSERT(g_DungeonManager != nullptr);
        if (g_DungeonManager != nullptr)
        {
            delete g_DungeonManager;
        }
    }

    /// @brief - Get all dungeons from a JSON file and register them
    void DungeonMgr::Init()
    {

    }

    bool DungeonMgr::RegisterNewDungeon(const std::string& id, const Dungeon::Dungeon* dungeon)
    {
        if (dungeonMap.find(id) != dungeonMap.end())
        {
            dungeonMap[id] = dungeon;
            return true;
        }
        return false;
    }

    Dungeon::Dungeon* DungeonMgr::GetCurrDungeon()
    {
        PKMD_ASSERT(currDungeon);
        return currDungeon;
    }


}
