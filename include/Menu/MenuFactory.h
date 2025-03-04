#ifndef MENU_FACTORY_H
#define MENU_FACTORY_H

#include "Menu.h"
#include "MenuType.h"
#include "Core/ApplicationCore.h"
#include <memory>

namespace menu
{

	class MenuFactory
	{
	public:
		explicit MenuFactory(core::ApplicationCore& appCore)
			: m_appCore(appCore) {}
	public:
		virtual ~MenuFactory() = default;

	public:
		[[nodiscard]] virtual std::unique_ptr<Menu> createMenu(MenuType type) = 0;
	
	protected:
		core::ApplicationCore& m_appCore;
	};

} // menu

#endif // MENU_FACTORY_H
