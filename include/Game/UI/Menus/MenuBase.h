#pragma once


namespace PKMD::Game::UI
{
	class MenuBase
	{
	protected:
		size_t m_menuId = -1;
		bool m_isOpen = false;
		int m_selection = 0;
		int m_numOptions = MenuTypes::MENU_MAX;

	public:
		bool IsOpen() const { return m_isOpen; }

		virtual void NavigateUp() { if (m_selection > 0) m_selection--; }
		virtual void NavigateDown() { if (m_selection < m_numOptions - 1) m_selection++; }
		virtual void Select() = 0;

		virtual void Toggle() = 0;
		virtual void Render() const = 0;

		size_t GetMenuID() const { return m_menuId; }
		void SetMenuID(size_t menuId) { m_menuId = menuId; }

		virtual void SubscribeEvents() = 0;

	};
}