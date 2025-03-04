#ifndef MENU_FACTORY_FACTORY_H
#define MENU_FACTORY_FACTORY_H

#include "MenuFactory.h"
#include "TUIMenuFactory.h"
#include "UI/UIType.h"
#include "Core/ApplicationCore.h"
#include <memory>
#include <stdexcept>

namespace menu
{

	class MenuFactoryFactory final
	{
	public:
		explicit MenuFactoryFactory(core::ApplicationCore& appCore)
			: m_appCore(appCore) {}

	public:

		[[nodiscard]] static std::unique_ptr<MenuFactory> createMenuFactory(ui::UIType type, core::ApplicationCore appCore)
		{
			if (type == ui::UIType::TUI) {
				return std::make_unique<TUIMenuFactory>(appCore);
			}
			else {
				throw std::invalid_argument("There is no such type of UI.");
			}
		}
	private:
		core::ApplicationCore m_appCore;
	};

} // namespace menu

#endif // MENU_FACTORY_FACTORY_H
