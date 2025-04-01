#include "Menu/EditMenu.h"

#include <conio.h>
#include "UI/ConsoleManager.h"
#include "Core/Utils.h"
#include "Message/ConfirmMSG.h"
#include "Message/FatalErrorMSG.h"

namespace menu
{
	EditMenu::EditMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		init();
	}

	void EditMenu::onRender() /*override*/
	{
		m_slider->onRender();
		m_CBBack->allowChanges(); m_CBBack->show();
	}

	void EditMenu::onUpdate() /*override*/
	{
		auto& sliderButtons = m_slider->getButtons();

		mouseButtonInteraction(
			sliderButtons[0].get(),
			sliderButtons[1].get(),
			sliderButtons[2].get(),
			sliderButtons[3].get(),
			sliderButtons[4].get(),
			sliderButtons[5].get(),
			sliderButtons[6].get(),
			m_CBBack.get()
		);
	}

	void EditMenu::init()
	{
		std::vector<std::vector<char>> backSym = {
			{char(201),	 char(205),	  char(205),   char(205),	 char(187)},
			{char(186),	 ' ',		  'X',		   ' ',		     char(186)},
			{char(200),	 char(205),	  char(205),   char(205),	 char(188)}
		};
		m_CBBack = std::make_unique<CustomButton>(backSym, backSym, 85, 1);
		m_slider = std::make_unique<ui::widgets::Slider>(5, 20, 3, 36, 5);
		m_editBox = std::make_unique<ui::widgets::EditBox>(30, 15, 56, 7);

		m_CBBack->setBackgroundColor(Blue);
		m_CBBack->setForegroundColor(White);

		connectButtons();
		updateSliderButtonsName();

		renderAll();
	}

	void EditMenu::editTeam(int indexOfTeam)
	{
		const auto teams = m_appCore.getTeams();
		if (indexOfTeam >= teams.size()) return;

		auto originalText = m_appCore.getTeam(teams[indexOfTeam]);
		m_editBox->setContent(core::utils::teamToLabeledText(originalText));

		ui::ConsoleManager::getInstance().clearScreen();
		renderEditMenu();

		handleEditLoop();

		auto content = m_editBox->getContent();
		cleanFileLines(content);
		auto resultText = core::utils::textToTeamDataList(content);
		if (confirmSave()) {
			saveTeamData(teams[indexOfTeam], resultText);
		}

		setPendingMenu(MenuType::MainMenu);
	}

	void EditMenu::handleEditLoop()
	{
		while (true) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 27) break; // esc
				m_editBox->onUpdate(key);
			}
			m_editBox->onRender();
		}
	}

	bool EditMenu::confirmSave()
	{
		bool needSave = false;
		std::unique_ptr<msg::ConfirmMSG> confirm_msg
			= std::make_unique<msg::ConfirmMSG>(65, 9, [&](bool bSave) {
			needSave = bSave;
				});

		confirm_msg->setTitle("SAVE THE CHANGES");
		confirm_msg->setPosition(27, 10);
		confirm_msg->run();
		return needSave;
	}

	void EditMenu::cleanFileLines(std::vector<std::string>& lines)
	{
		for (std::string& line : lines) {
			line.erase(line.find_last_not_of(" \t") + 1);
		}

		while (!lines.empty() && lines.back().empty()) {
			lines.pop_back();
		}
	}

	void EditMenu::displayError(const std::string& errorMessage)
	{
		std::unique_ptr<msg::FatalErrorMSG> notificationMSG
			= std::make_unique<msg::FatalErrorMSG>(63, 9);
		notificationMSG->setPosition(28, 10);
		notificationMSG->setTitle(errorMessage);
		notificationMSG->run();
	}

	void EditMenu::saveTeamData(const std::string& teamName, const std::vector<std::string>& resultText)
	{
		try {
			m_appCore.overwriteTeam(teamName, resultText);
		}
		catch (const std::runtime_error& e) {
			displayError(e.what());
		}
	}

	void EditMenu::renderAll()
	{
		Window mainFrame(62, 26, 29, 2);
		mainFrame.addWindowName("EDIT TEAM", 1, 0);
		mainFrame.show();

		Window sliderFrame(22, 23, 35, 4);
		sliderFrame.addWindowName("teams", 1, 0);
		sliderFrame.show();

		Window dialogWindow(26, 6, 60, 5);
		dialogWindow.addWindowName("dialog", 1, 0);
		dialogWindow.show();

		ui::ConsoleManager::getInstance().setCursorPosition(65, 7); std::cout << "SELECT THE TEAM";
		ui::ConsoleManager::getInstance().setCursorPosition(65, 8); std::cout << "YOU WANT TO EDIT";
	}

	void EditMenu::renderEditMenu()
	{
		Window editMenuFrame(61, 19, 29, 5);
		editMenuFrame.addWindowName("EDIT MENU", 1, 0);
		editMenuFrame.show();

		m_editBox->renderAll();

		Window msgFrame(20, 9, 32, 7);
		msgFrame.addWindowName("MSG", 1, 0);
		msgFrame.show();

		ui::ConsoleManager::getInstance().setCursorPosition(35, 9);
		std::cout << char(250) << ' ' << "TO EXIT";
		ui::ConsoleManager::getInstance().setCursorPosition(37, 11);
		std::cout << "PRESS KEY";
		ui::ConsoleManager::getInstance().setCursorPosition(37, 13);
		std::cout << "ESCAPE";
	}

	void EditMenu::connectButtons()
	{
		m_CBBack->connect([&]() {
			ui::ConsoleManager::getInstance().clearScreen();
			setPendingMenu(MenuType::MainMenu);
			});

		auto& sliderButtons = m_slider->getButtons();

		sliderButtons[0]->connect([&]() { sliderMoveUp(); updateSliderButtonsName(); });

		for (int i = 1; i < sliderButtons.size() - 1; ++i) {
			int indexOfTeam = i - 1;
			sliderButtons[i]->connect([this, indexOfTeam]() {
				this->editTeam(indexOfTeam + this->m_sliderShift);
				});
		}

		sliderButtons[m_slider->capacity() - 1]->connect([&]() { sliderMoveDown(); updateSliderButtonsName(); });

	}

	void EditMenu::updateSliderButtonsName()
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

	void EditMenu::sliderMoveUp()
	{
		if (m_sliderShift > 0)
			m_sliderShift--;
	}

	void EditMenu::sliderMoveDown()
	{
		if (m_sliderShift + m_slider->capacity() - 2 < m_appCore.getTeams().size())
			m_sliderShift++;
	}


} // namespace menu