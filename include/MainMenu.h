#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"
#include "ApplicationCore.h"
#include "GUI.h"

namespace menu
{

	class MainMenu final : public Menu
	{
	public:
		explicit MainMenu(core::ApplicationCore& appCore)
			: m_appCore(appCore) {}

	public:
		void onRender() override;
		void onUpdate() override;
	
	private:
		core::ApplicationCore& m_appCore;

	private:
		std::unique_ptr<
	};

} // namespace menu

#endif // MAIN_MENU_H
