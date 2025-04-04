#include "Menu/SortMenu.h"

#include "UI/ConsoleManager.h"
#include "Message/FatalErrorMSG.h"
#include "Message/NotificationMSG.h"
#include "Message/ConfirmMSG.h"
#include "Core/Utils.h"
#include "Core/Sort.h"
#include "window.h"

#include <algorithm>

namespace menu
{

	SortMenu::SortMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		init();
	}

	void SortMenu::onRender()
	{
		m_slider->onRender();
		m_textBox->onRender();
		m_PBSortSurname->allowChanges();	 m_PBSortSurname->show();
		m_PBSortAge->allowChanges();		 m_PBSortAge->show();
		m_PBSortHeight->allowChanges();		 m_PBSortHeight->show();
		m_PBSortGameNumber->allowChanges();	 m_PBSortGameNumber->show();
		m_PBAscending->allowChanges();		 m_PBAscending->show();
		m_PBDescending->allowChanges();		 m_PBDescending->show();
		m_CBBack->allowChanges();			 m_CBBack->show();
	}

	void SortMenu::onUpdate()
	{
		auto& sliderButtons		 = m_slider->getButtons();
		auto& textBoxUpButton	 = m_textBox->getUpButton();
		auto& textBoxDownButton	 = m_textBox->getDownButton();

		mouseButtonInteraction(
			sliderButtons[0].get(),
			sliderButtons[1].get(),
			sliderButtons[2].get(),
			sliderButtons[3].get(),
			sliderButtons[4].get(),
			sliderButtons[5].get(),
			sliderButtons[6].get(),
			textBoxUpButton.get(),
			textBoxDownButton.get(),
			m_PBSortSurname.get(),
			m_PBSortAge.get(),
			m_PBSortHeight.get(),
			m_PBSortGameNumber.get(),
			m_CBBack.get(),
			m_PBAscending.get(),
			m_PBDescending.get()
		);
	}

	void SortMenu::init()
	{
		m_PBSortSurname		 = std::make_unique<PushButton>(20, 3, "SORT BY SURNAME", 85, 5);
		m_PBSortAge			 = std::make_unique<PushButton>(20, 3, "SORT BY AGE", 85, 8);
		m_PBSortHeight		 = std::make_unique<PushButton>(20, 3, "SORT BY HEGIHT", 85, 11);
		m_PBSortGameNumber	 = std::make_unique<PushButton>(20, 3, "SORT BY GAME NUM", 85, 14);

		m_PBAscending		 = std::make_unique<PushButton>(20, 3, "ASCENDING", 85, 20);
		m_PBDescending		 = std::make_unique<PushButton>(20, 3, "DESCENDING", 85, 23);

		m_slider			 = std::make_unique<ui::widgets::Slider>(5, 20, 3, 15, 5);
		m_textBox			 = std::make_unique<ui::widgets::TextBox>(40, 21, 40, 5);

		std::vector<std::vector<char>> backSym = {
			{char(201),	 char(205),	  char(205),   char(205),	 char(187)},
			{char(186),	 ' ',		  'X',		   ' ',		     char(186)},
			{char(200),	 char(205),	  char(205),   char(205),	 char(188)}
		};
		m_CBBack = std::make_unique<CustomButton>(backSym, backSym, 101, 2);


		setupSortKeyButtonsColor();
		setupSortOrderButtonsColor();

		m_CBBack->setBackgroundColor(Blue);
		m_CBBack->setForegroundColor(White);

		connectButtons();
		updateSliderButtonsName();

		m_indexOfLastSortedTeam	 = -1;
		m_currentSortKey		 = SortKey::Unknown;
		m_currentSortOrder		 = SortOrder::Unknown;

		renderAll();
	}

	void SortMenu::connectButtons()
	{
		m_CBBack->connect([&]() {
			if (m_indexOfLastSortedTeam >= 0 && confirmSave()) {
				saveSortedTeam();
			}
			setPendingMenu(MenuType::MainMenu);
			});

		m_PBAscending->connect	([&]() { m_currentSortOrder = SortOrder::Ascending;	 proccessSortOrderButton(); });
		m_PBDescending->connect	([&]() { m_currentSortOrder = SortOrder::Descending; proccessSortOrderButton(); });

		m_PBSortSurname->connect	([&]() { m_currentSortKey = SortKey::Surname;		 proccessSortKeyButton(); });
		m_PBSortAge->connect		([&]() { m_currentSortKey = SortKey::Age;			 proccessSortKeyButton(); });
		m_PBSortHeight->connect		([&]() { m_currentSortKey = SortKey::Height;		 proccessSortKeyButton(); });
		m_PBSortGameNumber->connect	([&]() { m_currentSortKey = SortKey::GameNumber;	 proccessSortKeyButton(); });

		auto& sliderButtons = m_slider->getButtons();

		sliderButtons[0]->connect([&]() { sliderMoveUp(); updateSliderButtonsName(); });

		for (int i = 1; i < sliderButtons.size() - 1; ++i) {
			int indexOfTeam = i - 1;
			sliderButtons[i]->connect([this, indexOfTeam]() {
				if (m_indexOfLastSortedTeam >= 0 && m_indexOfLastSortedTeam != indexOfTeam + m_sliderShift) {
					if (this->confirmSave()) {
						saveSortedTeam();
					}
				}
				this->displayTeam(indexOfTeam + this->m_sliderShift);
				});
		}

		sliderButtons[m_slider->capacity() - 1]->connect([&]() { sliderMoveDown(); updateSliderButtonsName(); });

		auto& textBoxUpButton = m_textBox->getUpButton();
		auto& textBoxDownButton = m_textBox->getDownButton();

		textBoxUpButton->connect	([&]() { m_textBox->moveUp(); m_textBox->displayText(); });
		textBoxDownButton->connect	([&]() { m_textBox->moveDown(); m_textBox->displayText(); });

	}

	void SortMenu::setupSortKeyButtonsColor()
	{
		m_PBSortSurname->setBackgroundColor(White);
		m_PBSortSurname->setForegroundColor(Black);

		m_PBSortAge->setBackgroundColor(White);
		m_PBSortAge->setForegroundColor(Black);

		m_PBSortHeight->setBackgroundColor(White);
		m_PBSortHeight->setForegroundColor(Black);

		m_PBSortGameNumber->setBackgroundColor(White);
		m_PBSortGameNumber->setForegroundColor(Black);
	}

	void SortMenu::setupSortOrderButtonsColor()
	{
		m_PBAscending->setBackgroundColor(White);
		m_PBAscending->setForegroundColor(Black);

		m_PBDescending->setBackgroundColor(White);
		m_PBDescending->setForegroundColor(Black);
	}

	void SortMenu::renderAll()
	{
		Window mainFrame(94, 24, 13, 3);
		mainFrame.addWindowName("SORT TEAM", 1, 0);
		mainFrame.show();
		m_textBox->renderAll();
	}

	void SortMenu::updateSliderButtonsName()
	{
		auto& buttons = m_slider->getButtons();
		const std::vector<std::string>& teams = m_appCore.getTeams();

		if (buttons.size() < 2) {
			return;
		}

		for (size_t i = 1; i + 1 < buttons.size(); ++i) {
			size_t index = i - 1 + m_sliderShift;
			buttons[i]->setName(index < teams.size() ? teams[index] : "");
		}
	}

	void SortMenu::sliderMoveUp()
	{
		if (m_sliderShift > 0)
			m_sliderShift--;
	}

	void SortMenu::sliderMoveDown()
	{
		if (m_sliderShift + m_slider->capacity() - 2 < m_appCore.getTeams().size())
			m_sliderShift++;
	}

	void SortMenu::proccessSortKeyButton() {
		setupSortKeyButtonsColor(); 
		updateSortKeyButtons();
		displayTeam(m_indexOfLastSortedTeam);
	}

	void SortMenu::proccessSortOrderButton() {
		setupSortOrderButtonsColor();
		updateSortOrderButtons();
		displayTeam(m_indexOfLastSortedTeam);
	}

	void SortMenu::updateSortKeyButtons() {
		if (m_currentSortKey == SortKey::Surname) {
			m_PBSortSurname->setBackgroundColor(BrightRed);
		}
		else if (m_currentSortKey == SortKey::Age) {
			m_PBSortAge->setBackgroundColor(BrightRed);
		}
		else if (m_currentSortKey == SortKey::Height) {
			m_PBSortHeight->setBackgroundColor(BrightRed);
		}
		else if (m_currentSortKey == SortKey::GameNumber) {
			m_PBSortGameNumber->setBackgroundColor(BrightRed);
		}
	}

	void SortMenu::updateSortOrderButtons() {
		if (m_currentSortOrder == SortOrder::Ascending) {
			m_PBAscending->setBackgroundColor(BrightRed);
		}
		else if (m_currentSortOrder == SortOrder::Descending) {
			m_PBDescending->setBackgroundColor(BrightRed);
		}
	}

	void SortMenu::displayTeam(int indexOfTeam)
	{
		const auto teams = m_appCore.getTeams();
		if (indexOfTeam >= teams.size() || indexOfTeam < 0) return;

		try {
			auto teamname = teams[indexOfTeam];
			auto teamDataList = m_appCore.getTeam(teamname);
			if (!applySort(teamname, teamDataList)) return;
			
			m_indexOfLastSortedTeam = indexOfTeam;
			m_dataOfLastSortedTeam = std::move(teamDataList);
			m_textBox->setContent(core::utils::teamToLabeledText(m_dataOfLastSortedTeam));
		}
		catch (const std::runtime_error& e) {
			std::unique_ptr<msg::FatalErrorMSG> notificationMSG
				= std::make_unique<msg::FatalErrorMSG>(63, 9);
			notificationMSG->setPosition(28, 10);
			notificationMSG->setTitle(e.what());
			notificationMSG->run();
		}

		m_textBox->displayText();
	}
	
	bool SortMenu::applySort(const std::string& teamname, std::vector<std::string>& teamDataList)
	{
		if (m_currentSortKey == SortKey::Unknown) {
			handleNotification("CHOOSE SORT KEY!", 63, 9, 28, 10);
			return false;
		}

		if (m_currentSortOrder == SortOrder::Unknown) {
			handleNotification("CHOOSE SORT ORDER!", 63, 9, 28, 10);
			return false;
		}

		auto team = core::utils::textToTeam(teamname, teamDataList);
		auto players = team.getPlayers();

		auto comparator = [&](const core::Player& p1, const core::Player& p2) {
			switch (m_currentSortKey) {
			case SortKey::Surname:     return m_currentSortOrder == SortOrder::Ascending ? p1.getSurname() < p2.getSurname() : p1.getSurname() > p2.getSurname();
			case SortKey::Age:         return m_currentSortOrder == SortOrder::Ascending ? p1.getAge() < p2.getAge() : p1.getAge() > p2.getAge();
			case SortKey::Height:      return m_currentSortOrder == SortOrder::Ascending ? p1.getHeight() < p2.getHeight() : p1.getHeight() > p2.getHeight();
			case SortKey::GameNumber:  return m_currentSortOrder == SortOrder::Ascending ? p1.getGameNumber() < p2.getGameNumber() : p1.getGameNumber() > p2.getGameNumber();
			default: return false;
			}
			};

		core::utils::my_sort(players.begin(), players.end(), comparator);

		team.removeAllPlayers();
		team.addAllPlayers(players);
		teamDataList = core::utils::teamToText(team);

		return true;
	}

	void SortMenu::saveSortedTeam()
	{
		auto teamName = m_appCore.getTeams()[m_indexOfLastSortedTeam];

		try {
			m_appCore.overwriteTeam(teamName, m_dataOfLastSortedTeam);
		}
		catch (const std::runtime_error& e) {
			std::unique_ptr<msg::FatalErrorMSG> notificationMSG
				= std::make_unique<msg::FatalErrorMSG>(63, 9);
			notificationMSG->setPosition(28, 10);
			notificationMSG->setTitle(e.what());
			notificationMSG->run();
		}
	}

	void SortMenu::handleNotification(
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

	bool SortMenu::confirmSave()
	{
		bool needSave = false;
		std::unique_ptr<msg::ConfirmMSG> confirm_msg = std::make_unique<msg::ConfirmMSG>(65, 9, [&](bool bSave) {
			needSave = bSave;
			});

		confirm_msg->setTitle("WANT TO KEEP YOUR TEAM IN A SORTED PROCESS?");
		confirm_msg->setPosition(27, 10);
		confirm_msg->run();

		ui::ConsoleManager::getInstance().clearScreen();
		renderAll();

		return needSave;
	}

} // namespace menu