#pragma once
#include <Backend/Events/EventBus.h>


#include <Game/UI/Menus/MenuBase.h>
#include <Game/UI/MenuTypes.h>
#include <Game/UI/MenuManager.h>

#include <Backend/Input/InputTypes.h>

#include <raylib.h>
using namespace PKMD::Backend::Events;
using namespace PKMD::Backend::Input;

namespace PKMD::Game::UI
{
	class InGameMainMenu : public MenuBase
	{
	public:
		MenuTypes currActiveMenu = MENU_MAIN;

		void Select() override
		{
			std::cout << "Menu option " << m_selection << " selected!\n";
			currActiveMenu = (MenuTypes)m_selection;
		}

		void Toggle() override {
			m_isOpen = !m_isOpen;
			MenuManager* menuManager = MenuManager::Instance();
			menuManager->SetCurrentActiveMenu(MenuTypes::MENU_MAIN);
			currActiveMenu = MenuTypes::MENU_MAIN;
			std::cout << "Menu Toggled!\n";
		}

		void Render() const override {
			if (!IsOpen()) return;
			DrawRectangle(300, 200, 200, 150, LIGHTGRAY);
			for (int i = 0; i < m_numOptions; i++) {
				Color c = (i == m_selection) ? RED : BLACK;
				DrawText(TextFormat("Main Menu Item: ", i + 1), 320, 220 + i * 40, 20, c);
			}
		}

		void SubscribeEvents() override
		{
			EventBus& eventBus = *EventBus::Instance();
			eventBus.Subscribe<KeyReleasedEvent>([&](const KeyReleasedEvent& e)
				{
					switch (e.keyCode)
					{
					case KEY_SPACE:		Toggle(); break;
					case KEY_UP:		NavigateUp(); break;
					case KEY_DOWN:		NavigateDown(); break;
					case KEY_ENTER:		Select(); break;
					default:
						break;
					}
				},
				EventChannels::EVENT_TYPE_INPUT
			);
		}

	};
}