#include "Menu/DeleteMenu.h"

#include "UI/ConsoleManager.h"
#include "Message/FatalErrorMSG.h"
#include "Message/NotificationMSG.h"
#include "Message/ConfirmMSG.h"
#include "window.h"

namespace menu
{

	DeleteMenu::DeleteMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		init();
	}

	void DeleteMenu::onRender()
	{
		m_slider->onRender();
		m_CBBack->allowChanges(); m_CBBack->show();
	}

	void DeleteMenu::onUpdate()
	{
		auto& buttons = m_slider->getButtons();
		mouseButtonInteraction(
			buttons[0].get(),
			buttons[1].get(),
			buttons[2].get(),
			buttons[3].get(),
			buttons[4].get(),
			buttons[5].get(),
			buttons[6].get(),
			m_CBBack.get()
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
		m_slider = std::make_unique<ui::widgets::Slider>(5, 20, 3, 36, 5);

		std::vector<std::vector<char>> backSym = {
			{char(201),	 char(205),	  char(205),   char(205),	 char(187)},
			{char(186),	 ' ',		  'X',		   ' ',		     char(186)},
			{char(200),	 char(205),	  char(205),   char(205),	 char(188)}
		};
		m_CBBack = std::make_unique<CustomButton>(backSym, backSym, 85, 1);
		m_CBBack->setBackgroundColor(Blue);
		m_CBBack->setForegroundColor(White);

		connectButtons();
		updateButtonsName();

		renderAll();
	}

	void DeleteMenu::connectButtons()
	{
		m_CBBack->connect([&]() {
			ui::ConsoleManager::getInstance().clearScreen();
			setPendingMenu(MenuType::MainMenu);
			});

		auto& buttons = m_slider->getButtons();

		buttons[0]->connect([&]() { sliderMoveUp(); updateButtonsName(); });

		for (int i = 1; i < buttons.size() - 1; ++i) {
			int indexOfTeam = i - 1;
			buttons[i]->connect([this, indexOfTeam]() {
				this->deleteTeam(indexOfTeam + this->m_sliderShift);
				});
		}

		buttons[m_slider->capacity() - 1]->connect([&]() { sliderMoveDown(); updateButtonsName(); });
	}

	void DeleteMenu::deleteTeam(int indexOfTeam)
	{
		const auto teams = m_appCore.getTeams();
		if (indexOfTeam >= teams.size()) return;

		if (!confirmDelete())
			return;

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

	bool DeleteMenu::confirmDelete()
	{
		bool needDelete = false;
		std::unique_ptr<msg::ConfirmMSG> confirm_msg = std::make_unique<msg::ConfirmMSG>(65, 9, [&](bool bSave) {
			needDelete = bSave;
			});

		confirm_msg->setTitle("CONFIRM DELETION OF THE TEAM");
		confirm_msg->setPosition(27, 10);
		confirm_msg->run();

		if(!needDelete)
		{
			ui::ConsoleManager::getInstance().clearScreen();
			renderAll();
		}

		return needDelete;
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
		auto& buttons = m_slider->getButtons();
		const std::vector<std::string> teams = m_appCore.getTeams();
		for (int i = 1; i < buttons.size() - 1; i++) {
			buttons[i]->setName(
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
		if (m_sliderShift + m_slider->capacity() - 2 < m_appCore.getTeams().size())
			m_sliderShift++;
	}

} // namespace menu