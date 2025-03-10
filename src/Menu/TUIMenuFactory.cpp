#include "Menu/TUIMenuFactory.h"

#include "Menu/MainMenu.h"
#include "Menu/CreateMenu.h"
#include <stdexcept>

namespace menu
{
	std::unique_ptr<Menu> TUIMenuFactory::createMenu(MenuType type) /*override*/
	{
		if (type == MenuType::MainMenu) {
			return std::make_unique<MainMenu>(m_appCore);
		} else if (type == MenuType::CreateMenu) {
			return std::make_unique<CreateMenu>(m_appCore);
		}
		else {
			throw std::invalid_argument("There is no such type of Menu.");
		}
	}
} // namespace menu