#ifndef CREATE_MENU_H
#define CREATE_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"
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
		void init();
		void renderAll();
	
	private:	
		void handleNotification(std::string,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t);

	private:
		void handleEnterKey();
		bool isTeamNameDuplicate();

	private:
		core::ApplicationCore& m_appCore;

	private:
		std::unique_ptr<ui::widgets::EditLine> m_editLine;
		
	};

} // namespace menu

#endif // CREATE_MENU_H
