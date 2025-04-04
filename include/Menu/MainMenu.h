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
		void init();

	private:
		void createButtons();
		void connectButtons();
		void colorizeButtos();
		void renderAll();
		void renderImage();

	private:
		bool confirmCloseApplication();

	private:
		core::ApplicationCore& m_appCore;

	private:
		int m_select = -1;
		std::unique_ptr<PushButton> m_PBCreateTeam;
		std::unique_ptr<PushButton> m_PBAddPlayer;
		std::unique_ptr<PushButton> m_PBEditTeam;
		std::unique_ptr<PushButton> m_PBDeleteTeam;
		std::unique_ptr<PushButton> m_PBViewTeam;
		std::unique_ptr<PushButton> m_PBAnalytics;
		std::unique_ptr<PushButton> m_PBSort;
		std::unique_ptr<PushButton> m_PBQuit;
	};

} // namespace menu

#endif // MAIN_MENU_H
