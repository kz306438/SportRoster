#include "Menu/CreateMenu.h"

#include "UI/ConsoleManager.h"
#include "Menu/MainMenu.h"
#include "Message/NotificationMSG.h"
#include "window.h"
#include <conio.h>

namespace menu
{

	CreateMenu::CreateMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		m_editLine = std::make_unique<ui::widgets::EditLine>(48, 3, 36, 12, 14);
		renderAll();
	}

	void CreateMenu::onRender()
	{
		m_editLine->onRender();
	}

	void CreateMenu::onUpdate()
	{
		if (_kbhit())
		{
			int key = _getch();
			if (key == 27) {
				ui::ConsoleManager::getInstance().clearScreen();
				setPendingMenu(MenuType::MainMenu);
			}

			if (key == 13) {
				handleEnterKey();
			}

			m_editLine->onUpdate(key);
		}
	}

	void CreateMenu::renderAll()
	{
		Window mainFrame(58, 26, 31, 2);
		mainFrame.addWindowName("CREATE TEAM", 1, 0);
		mainFrame.show();

		Window dialogWindow(48, 6, 36, 5);
		dialogWindow.addWindowName("dialog", 1, 0);
		dialogWindow.show();

		ui::ConsoleManager::getInstance().setCursorPosition(50, 6); std::cout << "ENTER NEW TEAM NAME!";
		ui::ConsoleManager::getInstance().setCursorPosition(42, 8); std::cout << "TO ENTER A TEAM NAME, PRESS ENTER!";
		ui::ConsoleManager::getInstance().setCursorPosition(45, 9); std::cout << "TO EXIT PRESS THE ESCAPE KEY!";

		Window errorNotificationsWindow(48, 6, 36, 20);
		errorNotificationsWindow.addWindowName("error notifications", 1, 0);
		errorNotificationsWindow.show();

		saveConsoleAttributes();
		setColorBackground(BrightRed);
		
		ui::ConsoleManager::getInstance().setCursorPosition(45, 22); std::cout << "THE FILE NAME CANNOT BE EMPTY!";
		ui::ConsoleManager::getInstance().setCursorPosition(42, 24); std::cout << "MAXIMUM LINE LENGTH 14 CHARACTERS!";

		restoreConsoleAttributes();

		m_editLine->renderAll();

	}

	void CreateMenu::handleNotification(std::string title
		, std::uint16_t width
		, std::uint16_t height
		, std::uint16_t posX
		, std::uint16_t posY)
	{
		std::unique_ptr<msg::NotificationMSG> notificationMSG
			= std::make_unique<msg::NotificationMSG>(width, height);
		notificationMSG->setPosition(posX, posY);
		notificationMSG->setTitle(title);
		notificationMSG->run();
		ui::ConsoleManager::getInstance().clearScreen();
		renderAll();
	}

	void CreateMenu::handleEnterKey()
	{
		if (isTeamNameDuplicate()) {
			handleNotification("A TEAM WITH THE SAME NAME ALREADY EXISTS!", 63, 9, 28, 10);
		}
		else if(m_editLine->getText().size() == 0) {
			handleNotification("THE FILE NAME CANNOT BE EMPTY!", 63, 9, 28, 10);
		}
		else {
			m_appCore.createTeam(m_editLine->getText());
			handleNotification("FILE CREATED SUCCESSFULLY!", 63, 9, 28, 10);
			ui::ConsoleManager::getInstance().clearScreen();
			setPendingMenu(MenuType::MainMenu);
		}
	}

	bool CreateMenu::isTeamNameDuplicate()
	{
		std::vector<std::string> teams = m_appCore.getTeams();
		for (const auto& team : teams) {
			if (team == m_editLine->getText())
				return true;
		}
		return false;
	}

} // namespace menu