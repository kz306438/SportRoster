#include "TUIMenuFactory.h"

#include "MainMenu.h"
#include <stdexcept>

namespace menu
{
	std::unique_ptr<Menu> TUIMenuFactory::createMenu(MenuType type) /*override*/
	{
		if (type == MenuType::MainMenu) {
			return std::make_unique<MainMenu>();
		}
		else {
			throw std::invalid_argument("There is no such type of Menu.");
		}
	}
} // namespace menu