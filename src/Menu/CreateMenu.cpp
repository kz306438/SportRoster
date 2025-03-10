#include "Menu/CreateMenu.h"

#include "UI/ConsoleManager.h"
#include "Menu/MainMenu.h"

namespace menu
{

	CreateMenu::CreateMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		m_PBBack = std::make_unique<PushButton>(20, 5, "BACK", 10, 5);
		connectButtons();
	}

	void CreateMenu::onRender()
	{
		m_PBBack->allowChanges(); m_PBBack->show();
	}

	void CreateMenu::onUpdate()
	{
		mouseButtonInteraction(m_PBBack.get());

		if (m_select == 0) {
			ui::ConsoleManager::getInstance().clearScreen();
			setPendingMenu(MenuType::MainMenu);
		}

		m_select = -1;
	}

	void CreateMenu::connectButtons()
	{
		m_PBBack->connect([&]() { m_select = 0; });
	}

} // menu