#include "Menu/CreateMenu.h"

#include "UI/ConsoleManager.h"
#include "Menu/MainMenu.h"

#include <conio.h>

namespace menu
{

	CreateMenu::CreateMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		m_editLine = std::make_unique<ui::widgets::EditLine>(48, 3, 36, 14, 14);
		m_editLine->renderAll();
	}

	void CreateMenu::onRender()
	{
		m_editLine->onRender();
	}

	void CreateMenu::onUpdate()
	{
		if (_kbhit())
		{
			int key = _getch();
			if (key == 27) {
				ui::ConsoleManager::getInstance().clearScreen();
				setPendingMenu(MenuType::MainMenu);
			}

			m_editLine->onUpdate(key);
		}
	}

} // menu