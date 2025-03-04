#include "Menu/MainMenu.h"

#include "UI/ConsoleManager.h"
namespace menu
{
	/*explicit*/ MainMenu::MainMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore) 
	{
		m_PBQuit = std::make_unique<PushButton>(20, 5, "QUIT", 10, 5);
		connectButtons();
	}

	void MainMenu::onRender() /*override*/
	{		
		m_PBQuit->allowChanges(); m_PBQuit->show();
	}
	
	void MainMenu::onUpdate() /*override*/
	{
		mouseButtonInteraction(m_PBQuit.get());

		if (m_select == 0)
		{
			exit(0);
		}

		m_select = -1;
	}

	void MainMenu::connectButtons()
	{
		m_PBQuit->connect([&]() { m_select = 0; });
	}

} // namespace menu