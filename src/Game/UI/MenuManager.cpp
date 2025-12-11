#include <Game/UI/MenuManager.h>
#include <Game/UI/Menus/MenuBase.h>


namespace PKMD::Game::UI
{
	size_t MenuManager::RegisterMenu(std::unique_ptr<MenuBase> inMenu)
	{	
		size_t currID = inMenu.get()->GetMenuID();

		// Make sure it doesn't already exist
		if (currID != -1)
		{
			PKMD_INFO_ASSERT(false, "Registering Menu that was already registered!");
			return currID;
		}

		currID = 100; /*TODO: Use hash function here */
		// Insert into the map
		m_menuMap[currID] = std::move(inMenu);

		return currID;
	}
	void MenuManager::RenderMenu() const
	{
		const auto& currMenuIterator = m_menuMap.find(m_currActiveMenu);
		if (currMenuIterator == m_menuMap.end())
		{
			PKMD_INFO_ASSERT(false, "Current Menu not in map? How are you here - check registrations");
			return;
		}

		currMenuIterator->second.get()->Render();
		return;
	}
}