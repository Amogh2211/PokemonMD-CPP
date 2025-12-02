#include "Game/GameManager.h"
#include <filesystem>
#include <stdio.h>

// Should ideally make a logger at some point
using namespace PKMD::Game;

#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <algorithm>

#include <Backend/Types.h>



int main()
{
	/*GameManager::Create();

	GameManager* gameMgr = GameManager::Instance();
	
	std::filesystem::path cwd = std::filesystem::current_path();
	std::cout << "Current System Path: " << cwd << "\n";

	
	PKMD_ASSERT(gameMgr);

	PKMD_ASSERT(gameMgr->LoadAssets());*/

    //EventBus bus;

    size_t handle1 = bus.Subscribe<int>([](const int& x) {
        std::cout << "Got int event 1: " << x << "\n";
        });

    size_t handle2 = bus.Subscribe<int>([](const int& x) {
        std::cout << "Got int event 2: " << x << "\n";
        });
    
    bus.Emit<int>(42, handle1);
    bus.Emit<int>(100, handle2);


    bus.Unsubscribe<int>(handle1);
    bus.Unsubscribe<int>(handle2);
	return 0;
}