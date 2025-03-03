#ifndef MENU_FACTORY_FACTORY_H
#define MENU_FACTORY_FACTORY_H

#include "MenuFactory.h"
#include "TUIMenuFactory.h"
#include <memory>
#include <stdexcept>

namespace menu
{

	class MenuFactoryFactory
	{
	public:
		[[nodiscard]] static std::unique_ptr<MenuFactory> createMenuFactory(ui::UIType type)
		{
			if (type == ui::UIType::TUI) {
				return std::make_unique<TUIMenuFactory>();
			}
			else {
				throw std::invalid_argument("There is no such type of UI.");
			}
		}
	};

} // namespace menu

#endif // MENU_FACTORY_FACTORY_H
