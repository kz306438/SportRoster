#include "TUI.h"

#include "ConsoleManager.h"
#include "MenuFactoryFactory.h"
#include "TUIMenuFactory.h"

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
		m_menu->onRender();
	}

	void TUI::onUpdate() /*override*/
	{
		m_menu->onUpdate();
	}

	void TUI::setMenu(menu::MenuType type)
	{
		auto tuiMenuFactory = menu::MenuFactoryFactory::createMenuFactory(UIType::TUI, m_appCore);
		m_menu = tuiMenuFactory->createMenu(type);
	}

	void TUI::init()
	{
		ConsoleManager::getInstance().DisableResize();
		ConsoleManager::getInstance().SetSize(m_width, m_height);
		ConsoleManager::getInstance().SetTitle(m_title);
	}

} // namespace ui