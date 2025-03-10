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
		menu::MenuType menuType = m_currentMenu->getPendingMenu();
		if (menuType != menu::MenuType::Unknown) {
			m_currentMenu = m_menuFactory->createMenu(menuType);
		}

		m_currentMenu->onUpdate();
	}

	void TUI::init()
	{
		ConsoleManager::getInstance().DisableResize();
		ConsoleManager::getInstance().SetSize(m_width, m_height);
		ConsoleManager::getInstance().SetTitle(m_title);
		ConsoleManager::getInstance().SetCursorVisibility(false);

		setupInputHandling();

		m_menuFactory = menu::MenuFactoryFactory::createMenuFactory(UIType::TUI, m_appCore);
		m_currentMenu = m_menuFactory->createMenu(menu::MenuType::MainMenu);
	}

} // namespace ui