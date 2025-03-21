#include "Menu/DeleteMenu.h"

#include "UI/ConsoleManager.h"
#include "Message/FatalErrorMSG.h"
#include "Message/NotificationMSG.h"
#include "window.h"

namespace menu
{

	DeleteMenu::DeleteMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore), Slider(5, 20, 3, 36, 5)
	{
		init();
	}

	void DeleteMenu::onRender()
	{
		m_buttons[0]->allowChanges(); m_buttons[0]->show();
		m_buttons[1]->allowChanges(); m_buttons[1]->show();
		m_buttons[2]->allowChanges(); m_buttons[2]->show();
		m_buttons[3]->allowChanges(); m_buttons[3]->show();
		m_buttons[4]->allowChanges(); m_buttons[4]->show();
		m_buttons[5]->allowChanges(); m_buttons[5]->show();
		m_buttons[6]->allowChanges(); m_buttons[6]->show();
		m_PBBack->allowChanges(); m_PBBack->show();
	}

	void DeleteMenu::onUpdate()
	{
		mouseButtonInteraction(
			m_buttons[0].get(),
			m_buttons[1].get(),
			m_buttons[2].get(),
			m_buttons[3].get(),
			m_buttons[4].get(),
			m_buttons[5].get(),
			m_buttons[6].get(),
			m_PBBack.get()
		);
	}

	void DeleteMenu::renderAll()
	{
		Window mainFrame(62, 26, 29, 2);
		mainFrame.addWindowName("DELETE TEAM", 1, 0);
		mainFrame.show();

		Window sliderFrame(22, 23, 35, 4);
		sliderFrame.addWindowName("teams", 1, 0);
		sliderFrame.show();

		Window dialogWindow(26, 6, 60, 5);
		dialogWindow.addWindowName("dialog", 1, 0);
		dialogWindow.show();

		ui::ConsoleManager::getInstance().setCursorPosition(65, 7); std::cout << "SELECT THE TEAM";
		ui::ConsoleManager::getInstance().setCursorPosition(63, 8); std::cout << "YOU WANT TO DELETE";
	}

	void DeleteMenu::init()
	{
		m_PBBack = std::make_unique<PushButton>(20, 5, "BACK", 62, 21);
		m_PBBack->setBackgroundColor(White);
		m_PBBack->setForegroundColor(Black);

		connectButtons();
		updateButtonsName();

		renderAll();
	}

	void DeleteMenu::connectButtons()
	{
		m_PBBack->connect([&]() {
			ui::ConsoleManager::getInstance().clearScreen();
			setPendingMenu(MenuType::MainMenu);
			});

		m_buttons[0]->connect([&]() { sliderMoveUp(); updateButtonsName(); });

		for (size_t i = 1; i < m_buttons.size() - 1; ++i) {
			int indexOfTeam = i - 1;
			m_buttons[i]->connect([this, indexOfTeam]() {
				this->deleteTeam(indexOfTeam + this->m_sliderShift);
				});
		}

		m_buttons[m_capacity - 1]->connect([&]() { sliderMoveDown(); updateButtonsName(); });
	}

	void DeleteMenu::deleteTeam(int indexOfTeam)
	{
		const auto teams = m_appCore.getTeams();
		if (indexOfTeam >= teams.size()) return;

		try {
			m_appCore.deleteTeam(teams[indexOfTeam]);
		}
		catch (const std::invalid_argument& e) {
			std::unique_ptr<msg::FatalErrorMSG> notificationMSG
				= std::make_unique<msg::FatalErrorMSG>(63, 9);
			notificationMSG->setPosition(28, 10);
			notificationMSG->setTitle(e.what());
			notificationMSG->run();
		}
		handleNotification("TEAM " + teams[indexOfTeam] + " SUCCESSFULLY DELETED!", 69, 9, 25, 10);
		ui::ConsoleManager::getInstance().clearScreen();
		setPendingMenu(MenuType::MainMenu);
	}

	void DeleteMenu::handleNotification(
		std::string title,
		std::uint16_t width,
		std::uint16_t height,
		std::uint16_t posX,
		std::uint16_t posY)
	{
		std::unique_ptr<msg::NotificationMSG> notificationMSG
			= std::make_unique<msg::NotificationMSG>(width, height);
		notificationMSG->setPosition(posX, posY);
		notificationMSG->setTitle(title);
		notificationMSG->run();
		ui::ConsoleManager::getInstance().clearScreen();
		renderAll();
	}

	void DeleteMenu::updateButtonsName()
	{
		const std::vector<std::string> teams = m_appCore.getTeams();
		for (int i = 1; i < m_buttons.size() - 1; i++) {
			m_buttons[i]->setName(
				(i - 1 + m_sliderShift < teams.size()) ?
				teams[i - 1 + m_sliderShift]
				: "");
		}
	}

	void DeleteMenu::sliderMoveUp()
	{
		if (m_sliderShift > 0)
			m_sliderShift--;
	}

	void DeleteMenu::sliderMoveDown()
	{
		if (m_sliderShift + m_capacity - 2 < m_appCore.getTeams().size())
			m_sliderShift++;
	}

} // namespace menu