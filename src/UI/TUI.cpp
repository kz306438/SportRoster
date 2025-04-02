#include "UI/TUI.h"

#include "UI/ConsoleManager.h"
#include "Menu/MenuFactoryFactory.h"
#include "Menu/TUIMenuFactory.h"
#include "GUI.h"
#include <Menu/CreateMenu.h>
#include <Menu/MainMenu.h>
namespace ui
{
	TUI::TUI(std::uint16_t width, std::uint16_t height, core::ApplicationCore& appCore) noexcept
		: UI(width, height), m_appCore(appCore)
	{
		init();
	}

	TUI::TUI(std::uint16_t width, std::uint16_t height, std::string title, core::ApplicationCore& appCore)
		: UI(width, height, title), m_appCore(appCore)
	{
		init();
	}
	
	void TUI::onRender() /*override*/
	{
		m_currentMenu->onRender();
	}

	void TUI::onUpdate() /*override*/
	{
		m_currentMenu->onUpdate();
		
		menu::MenuType menuType = m_currentMenu->getPendingMenu();
		if (menuType != menu::MenuType::Unknown) {
			ConsoleManager::getInstance().clearScreen();
			m_currentMenu = m_menuFactory->createMenu(menuType);
		}
	}

	void TUI::init()
	{
		ConsoleManager::getInstance().disableResize();
		ConsoleManager::getInstance().setSize(m_width, m_height);
		ConsoleManager::getInstance().setTitle(m_title);
		ConsoleManager::getInstance().setCursorVisibility(false);
		ui::ConsoleManager::getInstance().setColorBackground(Blue);
		ui::ConsoleManager::getInstance().clearScreen();

		setupInputHandling();

		m_menuFactory = menu::MenuFactoryFactory::createMenuFactory(UIType::TUI, m_appCore);
		m_currentMenu = m_menuFactory->createMenu(menu::MenuType::MainMenu);
	}

} // namespace ui