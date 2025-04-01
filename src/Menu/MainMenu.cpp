#include "Menu/MainMenu.h"

#include "UI/ConsoleManager.h"
#include <UI/UI.h>
#include <memory>
#include "Menu/CreateMenu.h"
#include "Message/ConfirmMSG.h"

namespace menu
{
	/*explicit*/ MainMenu::MainMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		createButtons();
		connectButtons();
		colorizeButtos();
	}

	void MainMenu::onRender() /*override*/
	{
		m_PBCreateTeam->allowChanges();			 m_PBCreateTeam->show();
		m_PBAddPlayer->allowChanges();			 m_PBAddPlayer->show();
		m_PBEditTeam->allowChanges();			 m_PBEditTeam->show();
		m_PBDeleteTeam->allowChanges();			 m_PBDeleteTeam->show();
		m_PBViewTeam->allowChanges();			 m_PBViewTeam->show();
		m_PBAnalytics->allowChanges();	 m_PBAnalytics->show();
		m_PBSort->allowChanges();				 m_PBSort->show();
		m_PBQuit->allowChanges();				 m_PBQuit->show();
	}

	void MainMenu::onUpdate() /*override*/
	{
		mouseButtonInteraction(m_PBCreateTeam.get(), m_PBAddPlayer.get(), m_PBEditTeam.get(),
			m_PBDeleteTeam.get(), m_PBViewTeam.get(), m_PBAnalytics.get(),
			m_PBSort.get(), m_PBQuit.get());


		if (m_select == 0) {
			setPendingMenu(MenuType::CreateMenu);
		}
		else if (m_select == 1) {
			setPendingMenu(MenuType::AddPlayerMenu);
		}
		else if (m_select == 2) {
			setPendingMenu(MenuType::EditMenu);
		}
		else if (m_select == 3) {
			setPendingMenu(MenuType::DeleteMenu);
		}
		else if (m_select == 4) {
			setPendingMenu(MenuType::ViewTeamMenu);
		}
		else if (m_select == 5) {
			setPendingMenu(MenuType::AnalyticsMenu);
		}
		else if (m_select == 6) {
			setPendingMenu(MenuType::SortMenu);
		}
		else if (m_select == 7) {
			if (confirmCloseApplication())
				exit(0);
		}

		m_select = -1;
	}

	void MainMenu::createButtons()
	{
		m_PBCreateTeam = std::make_unique<PushButton>(30, 3, "CREATE TEAM", 50, 14);
		m_PBAddPlayer = std::make_unique<PushButton>(30, 3, "ADD PLAYER", 50, 17);
		m_PBEditTeam = std::make_unique<PushButton>(30, 3, "EDIT TEAM", 50, 20);
		m_PBDeleteTeam = std::make_unique<PushButton>(30, 3, "DELETE TEAM", 50, 23);
		m_PBViewTeam = std::make_unique<PushButton>(30, 3, "VIEW TEAM", 85, 14);
		m_PBAnalytics = std::make_unique<PushButton>(30, 3, "ANALYTICS", 85, 17);
		m_PBSort = std::make_unique<PushButton>(30, 3, "SORT", 85, 20);
		m_PBQuit = std::make_unique<PushButton>(30, 3, "QUIT", 85, 23);
	}

	void MainMenu::connectButtons()
	{
		m_PBCreateTeam->connect([&]() { m_select = 0; });
		m_PBAddPlayer->connect([&]() { m_select = 1; });
		m_PBEditTeam->connect([&]() { m_select = 2; });
		m_PBDeleteTeam->connect([&]() { m_select = 3; });
		m_PBViewTeam->connect([&]() { m_select = 4; });
		m_PBAnalytics->connect([&]() { m_select = 5; });
		m_PBSort->connect([&]() { m_select = 6; });
		m_PBQuit->connect([&]() { m_select = 7; });
	}

	void MainMenu::colorizeButtos()
	{
		m_PBCreateTeam->setBackgroundColor(White);
		m_PBCreateTeam->setForegroundColor(Black);

		m_PBAddPlayer->setBackgroundColor(White);
		m_PBAddPlayer->setForegroundColor(Black);

		m_PBEditTeam->setBackgroundColor(White);
		m_PBEditTeam->setForegroundColor(Black);

		m_PBDeleteTeam->setBackgroundColor(White);
		m_PBDeleteTeam->setForegroundColor(Black);

		m_PBViewTeam->setBackgroundColor(White);
		m_PBViewTeam->setForegroundColor(Black);

		m_PBAnalytics->setBackgroundColor(White);
		m_PBAnalytics->setForegroundColor(Black);

		m_PBSort->setBackgroundColor(White);
		m_PBSort->setForegroundColor(Black);

		m_PBQuit->setBackgroundColor(White);
		m_PBQuit->setForegroundColor(Black);
	}

	bool MainMenu::confirmCloseApplication()
	{
		bool shouldeClose = false;
		std::unique_ptr<msg::ConfirmMSG> confirm_msg = std::make_unique<msg::ConfirmMSG>(65, 9, [&](bool bSave) {
			shouldeClose = bSave;
			});

		confirm_msg->setTitle("CONFIRM CLOSING THE APPLICATION");
		confirm_msg->setPosition(27, 10);
		confirm_msg->run();

		if (!shouldeClose) {
			ui::ConsoleManager::getInstance().clearScreen();
		}

		return shouldeClose;
	}

} // namespace menu