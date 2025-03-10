#include "Menu/MainMenu.h"

#include "UI/ConsoleManager.h"
#include <UI/UI.h>
#include <memory>
#include "Menu/CreateMenu.h"

namespace menu
{
	/*explicit*/ MainMenu::MainMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore) 
	{
		m_PBCreateTeam		 = std::make_unique<PushButton>(30, 3, "CREATE TEAM", 50, 14);
		m_PBAddPlayer		 = std::make_unique<PushButton>(30, 3, "ADD PLAYER", 50, 17);
		m_PBEditTeam		 = std::make_unique<PushButton>(30, 3, "EDIT TEAM", 50, 20);
		m_PBDeleteTeam		 = std::make_unique<PushButton>(30, 3, "DELETE TEAM", 50, 23);
		m_PBViewTeam		 = std::make_unique<PushButton>(30, 3, "VIEW TEAM", 85, 14);
		m_PBViewYoungestTeam = std::make_unique<PushButton>(30, 3, "VIEW YOUNGEST TEAM", 85, 17);
		m_PBSort			 = std::make_unique<PushButton>(30, 3, "SORT", 85, 20);
		m_PBQuit			 = std::make_unique<PushButton>(30, 3, "QUIT", 85, 23);
		connectButtons();
	}

	void MainMenu::onRender() /*override*/
	{		
		m_PBCreateTeam->allowChanges();			 m_PBCreateTeam->show();
		m_PBAddPlayer->allowChanges();			 m_PBAddPlayer->show();
		m_PBEditTeam->allowChanges();			 m_PBEditTeam->show();
		m_PBDeleteTeam->allowChanges();			 m_PBDeleteTeam->show();
		m_PBViewTeam->allowChanges();			 m_PBViewTeam->show();
		m_PBViewYoungestTeam->allowChanges();	 m_PBViewYoungestTeam->show();
		m_PBSort->allowChanges();				 m_PBSort->show();
		m_PBQuit->allowChanges();				 m_PBQuit->show();
	}
	
	void MainMenu::onUpdate() /*override*/
	{
		mouseButtonInteraction(m_PBCreateTeam.get(), m_PBAddPlayer.get(), m_PBEditTeam.get(),
			m_PBDeleteTeam.get(), m_PBViewTeam.get(), m_PBViewYoungestTeam.get(), 
			m_PBSort.get(), m_PBQuit.get());


		if (m_select == 0)
		{
			setPendingMenu(MenuType::CreateMenu);
		}

		if (m_select == 1)
		{
			exit(0);
		}
		


		m_select = -1;
		
	}

	void MainMenu::connectButtons()
	{
		m_PBCreateTeam->connect([&]() { m_select = 0; });
		m_PBQuit->connect([&]() { m_select = 1; });
	}

} // namespace menu