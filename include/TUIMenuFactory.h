#ifndef TUI_MENU_FACTORY_H
#define TUI_MENU_FACTORY_H

#include "MenuFactory.h"
#include "MenuType.h"

namespace menu
{

	class TUIMenuFactory final: public MenuFactory
	{
	public:
		[[nodiscard]] std::unique_ptr<Menu> createMenu(MenuType type) override;
	};

} // namespace menu

#endif // TUI_MENU_FACTORY_H
