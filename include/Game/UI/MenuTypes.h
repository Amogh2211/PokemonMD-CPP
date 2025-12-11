#pragma once
#include <Backend/Types.h>

namespace PKMD::Game::UI
{
	enum MenuTypes
	{
		MENU_MAIN = 0,
		MENU_MOVE = 1,
		MENU_ITEMS = 2,
		MENU_INFO = 3,
		MENU_MAX,
		MENU_INVALID = -1,
	};

	const std::vector<std::string> menuTypesString =
	{
		"MENU_INVALID",
		"MENU_MAIN",
		"MENU_MOVE",
		"MENU_ITEMS",
		"MENU_INFO",
		"MENU_MAX"
	};

}