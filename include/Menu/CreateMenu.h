#ifndef CREATE_MENU_H
#define CREATE_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"
#include "GUI.h"
#include "UI/Widgets/EditLine.h"

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
		core::ApplicationCore& m_appCore;

	private:
		std::unique_ptr<ui::widgets::EditLine> m_editLine;
		
	};

} // namespace menu

#endif // CREATE_MENU_H
