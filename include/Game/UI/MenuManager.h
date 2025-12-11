#pragma once
#include <Backend/Types.h>
#include <Game/UI/MenuTypes.h>

namespace PKMD::Game::UI
{
	
	class MenuBase;
	class MenuManager : public PKMD::Singleton<MenuManager, true>
	{
		using MenuID = size_t;
		MenuID m_currActiveMenu = -1;
		std::map<MenuID, std::unique_ptr<MenuBase>> m_menuMap;
	public:

		size_t RegisterMenu(std::unique_ptr<MenuBase> inMenu);
		
		void SetCurrentActiveMenu(MenuTypes menuType)
		{
			m_currActiveMenu = menuType;
		};


		void RenderMenu() const;
	};
}