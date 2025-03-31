#include "Menu/TUIMenuFactory.h"

#include "Menu/MainMenu.h"
#include "Menu/CreateMenu.h"
#include "Menu/AddPlayerMenu.h"
#include "Menu/EditMenu.h"
#include "Menu/DeleteMenu.h"
#include "Menu/ViewTeamMenu.h"
#include "Menu/AnalyticsMenu.h"
#include "Menu/SortMenu.h"
#include <stdexcept>

namespace menu
{
	std::unique_ptr<Menu> TUIMenuFactory::createMenu(MenuType type) /*override*/
	{
		if (type == MenuType::MainMenu) {
			return std::make_unique<MainMenu>(m_appCore);
		} else if (type == MenuType::CreateMenu) {
			return std::make_unique<CreateMenu>(m_appCore);
		} else if (type == MenuType::AddPlayerMenu) {
			return std::make_unique<AddPlayerMenu>(m_appCore);
		} else if (type == MenuType::EditMenu) {
			return std::make_unique<EditMenu>(m_appCore);
		} else if (type == MenuType::DeleteMenu) {
			return std::make_unique<DeleteMenu>(m_appCore);
		} else if (type == MenuType::ViewTeamMenu) {
			return std::make_unique<ViewTeamMenu>(m_appCore);
		} else if (type == MenuType::AnalyticsMenu) {
			return std::make_unique<AnalyticsMenu>(m_appCore);
		} else if (type == MenuType::SortMenu) {
			return std::make_unique<SortMenu>(m_appCore);
		}
		else {
			throw std::invalid_argument("There is no such type of Menu.");
		}
	}
} // namespace menu