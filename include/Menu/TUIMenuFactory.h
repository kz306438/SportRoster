#ifndef TUI_MENU_FACTORY_H
#define TUI_MENU_FACTORY_H

#include "MenuFactory.h"
#include "MenuType.h"

#include "Core/ApplicationCore.h"

namespace menu
{

	class TUIMenuFactory final: public MenuFactory
	{
	public:
		explicit TUIMenuFactory(core::ApplicationCore& appCore)
			: MenuFactory(appCore) {};

	public:
		[[nodiscard]] std::unique_ptr<Menu> createMenu(MenuType type) override;
	};

} // namespace menu

#endif // TUI_MENU_FACTORY_H
