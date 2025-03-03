#ifndef MENU_FACTORY_H
#define MENU_FACTORY_H

#include "Menu.h"
#include "MenuType.h"
#include <memory>

namespace menu
{

	class MenuFactory
	{
	public:
		[[nodiscard]] virtual std::unique_ptr<Menu> createMenu(MenuType type) = 0;
	};

} // menu

#endif // MENU_FACTORY_H
