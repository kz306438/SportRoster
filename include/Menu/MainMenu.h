#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"
#include "Core/ApplicationCore.h"
#include "GUI.h"

namespace menu
{

	class MainMenu final : public Menu
	{
	public:
		explicit MainMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;
	private:
		void connectButtons();

	private:
		core::ApplicationCore& m_appCore;

	private:
		int m_select = -1;
		std::unique_ptr<PushButton> m_PBCreateTeam;
		std::unique_ptr<PushButton> m_PBAddPlayer;
		std::unique_ptr<PushButton> m_PBEditTeam;
		std::unique_ptr<PushButton> m_PBDeleteTeam;
		std::unique_ptr<PushButton> m_PBViewTeam;
		std::unique_ptr<PushButton> m_PBViewYoungestTeam;
		std::unique_ptr<PushButton> m_PBSort;
		std::unique_ptr<PushButton> m_PBQuit;
	};

} // namespace menu

#endif // MAIN_MENU_H
