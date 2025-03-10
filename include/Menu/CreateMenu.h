#ifndef CREATE_MENU_H
#define CREATE_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"
#include "GUI.h"

namespace menu
{

	class CreateMenu final : public Menu
	{
	public:
		explicit CreateMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;

	private:
		void connectButtons();

	private:
		core::ApplicationCore& m_appCore;

	private:
		int m_select = -1;
		std::unique_ptr<PushButton> m_PBBack;
		
	};

} // namespace menu

#endif // CREATE_MENU_H
