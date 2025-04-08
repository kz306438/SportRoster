#include "Menu/AnalyticsMenu.h"

#include "UI/ConsoleManager.h"
#include "UI/Widgets/EditLine.h" 
#include "Message/FatalErrorMSG.h"
#include "Message/NotificationMSG.h"
#include "Core/Utils.h"
#include "window.h"

#include <sstream>
#include <iomanip>
#include <optional>
#include <ranges>
#include <conio.h>

namespace menu
{
	/*explicit*/ AnalyticsMenu::AnalyticsMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		init();
	}

	void AnalyticsMenu::onRender() /*override*/
	{
		m_slider->onRender();
		m_textBox->onRender();
		m_PBAverageTeamStats->allowChanges();			m_PBAverageTeamStats->show();
		m_PBAverageOverallStats->allowChanges();		m_PBAverageOverallStats->show();
		m_PBYoungestTeam->allowChanges();		m_PBYoungestTeam->show();
		m_PBHighestTeam->allowChanges();		m_PBHighestTeam->show();
		m_PBFindPlayer->allowChanges();			m_PBFindPlayer->show();
		m_CBBack->allowChanges();				m_CBBack->show();
	}

	void AnalyticsMenu::onUpdate() /*override*/
	{
		auto& sliderButtons = m_slider->getButtons();
		auto& textBoxUpButton = m_textBox->getUpButton();
		auto& textBoxDownButton = m_textBox->getDownButton();

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
			m_PBAverageTeamStats.get(),
			m_PBAverageOverallStats.get(),
			m_PBYoungestTeam.get(),
			m_PBHighestTeam.get(),
			m_PBFindPlayer.get(),
			m_CBBack.get()
		);
	}

	void AnalyticsMenu::init()
	{
		m_PBAverageTeamStats	 = std::make_unique<PushButton>(20, 3, "TEAM AVG STATS", 85, 5);
		m_PBAverageOverallStats	 = std::make_unique<PushButton>(20, 3, "OVERALL AVG STATS", 85, 8);
		m_PBYoungestTeam		 = std::make_unique<PushButton>(20, 3, "YOUNGEST TEAM", 85, 14);
		m_PBHighestTeam			 = std::make_unique<PushButton>(20, 3, "HIGHEST TEAM", 85, 17);
		m_PBFindPlayer			 = std::make_unique<PushButton>(20, 3, "FIND PLAYER", 85, 23);

		m_slider	 = std::make_unique<ui::widgets::Slider>(5, 20, 3, 15, 5);
		m_textBox	 = std::make_unique<ui::widgets::TextBox>(40, 21, 40, 5);

		std::vector<std::vector<char>> backSym = {
			{char(201),	 char(205),	  char(205),   char(205),	 char(187)},
			{char(186),	 ' ',		  'X',		   ' ',		     char(186)},
			{char(200),	 char(205),	  char(205),   char(205),	 char(188)}
		};
		m_CBBack = std::make_unique<CustomButton>(backSym, backSym, 101, 2);

		m_CBBack->setBackgroundColor(Blue);
		m_CBBack->setForegroundColor(White);

		setupAnalyticsButtonsColor();

		connectButtons();
		updateSliderButtonsName();

		m_currentAnalysticsCriterion = AnalyticsCriterion::Unknown;

		renderAll();
	}

	void AnalyticsMenu::connectButtons()
	{
		m_CBBack->connect([&]() {
			ui::ConsoleManager::getInstance().clearScreen();
			setPendingMenu(MenuType::MainMenu);
			});

		m_PBAverageTeamStats->connect([&]() {
			m_currentAnalysticsCriterion = AnalyticsCriterion::AverageTeamStats;
			proccessAnalyticsButtons();
			m_PBAverageTeamStats->setBackgroundColor(BrightRed); 
			m_textBox->setContent(generateFileSelectionMessage());
			m_textBox->displayText();
			});

		m_PBAverageOverallStats->connect([&]() {
			m_currentAnalysticsCriterion = AnalyticsCriterion::AverageOverallStats;
			proccessAnalyticsButtons();
			m_PBAverageOverallStats->setBackgroundColor(BrightRed);
			displayTotalInformation(); });

		m_PBYoungestTeam->connect([&]() {
			m_currentAnalysticsCriterion = AnalyticsCriterion::YoungestTeam;
			proccessAnalyticsButtons();
			m_PBYoungestTeam->setBackgroundColor(BrightRed);
			displayTotalInformation(); });

		m_PBHighestTeam->connect([&]() {
			m_currentAnalysticsCriterion = AnalyticsCriterion::HighestTeam;
			proccessAnalyticsButtons();
			m_PBHighestTeam->setBackgroundColor(BrightRed);
			displayTotalInformation(); });

		m_PBFindPlayer->connect([&]() {
			m_currentAnalysticsCriterion = AnalyticsCriterion::FindPlayer;
			proccessAnalyticsButtons();
			m_PBFindPlayer->setBackgroundColor(BrightRed);
			m_textBox->setContent(generateFileSelectionMessage());
			m_textBox->displayText();
			});

		auto& sliderButtons = m_slider->getButtons();

		sliderButtons[0]->connect([&]() { sliderMoveUp(); updateSliderButtonsName(); });

		for (int i = 1; i < sliderButtons.size() - 1; ++i) {
			int indexOfTeam = i - 1;
			sliderButtons[i]->connect([this, indexOfTeam]() {
				if(isLocalTeamCriterion()) defaultDisplay(indexOfTeam + m_sliderShift);
				});
		}

		sliderButtons[m_slider->capacity() - 1]->connect([&]() { sliderMoveDown(); updateSliderButtonsName(); });

		auto& textBoxUpButton = m_textBox->getUpButton();
		auto& textBoxDownButton = m_textBox->getDownButton();

		textBoxUpButton->connect([&]() { m_textBox->moveUp(); m_textBox->displayText(); });
		textBoxDownButton->connect([&]() { m_textBox->moveDown(); m_textBox->displayText(); });
	}

	void AnalyticsMenu::setupAnalyticsButtonsColor()
	{
		m_PBAverageTeamStats->setBackgroundColor(White);
		m_PBAverageTeamStats->setForegroundColor(Black);

		m_PBAverageOverallStats->setBackgroundColor(White);
		m_PBAverageOverallStats->setForegroundColor(Black);

		m_PBYoungestTeam->setBackgroundColor(White);
		m_PBYoungestTeam->setForegroundColor(Black);

		m_PBHighestTeam->setBackgroundColor(White);
		m_PBHighestTeam->setForegroundColor(Black);

		m_PBFindPlayer->setBackgroundColor(White);
		m_PBFindPlayer->setForegroundColor(Black);
	}

	void AnalyticsMenu::renderAll()
	{
		Window mainFrame(94, 24, 13, 3);
		mainFrame.addWindowName("ANALYTICS", 1, 0);
		mainFrame.show();
		m_textBox->renderAll();
	}

	void AnalyticsMenu::proccessAnalyticsButtons()
	{
		setupAnalyticsButtonsColor();
	}

	void AnalyticsMenu::updateSliderButtonsName()
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

	void AnalyticsMenu::sliderMoveUp()
	{
		if (m_sliderShift > 0)
			m_sliderShift--;
	}

	void AnalyticsMenu::sliderMoveDown()
	{
		if (m_sliderShift + m_slider->capacity() - 2 < m_appCore.getTeams().size())
			m_sliderShift++;
	}

	void AnalyticsMenu::defaultDisplay(int indexOfTeam)
	{
		const auto teams = m_appCore.getTeams();
		if (indexOfTeam >= teams.size()) return;

		if (m_currentAnalysticsCriterion == AnalyticsCriterion::Unknown) {
			handleNotification("CHOOSE ANALYTICS CRITERION!", 63, 9, 28, 10);
			return;
		}

		try {
			std::vector<std::string> displayText;

			auto teamname = teams[indexOfTeam];
			auto teamDataList = m_appCore.getTeam(teamname);

			displayText = applyAnalyticsCriterion(teamname, teamDataList);

			m_textBox->setContent(displayText);
		}
		catch (const std::runtime_error& e) {
			handleFatalErrorMSG(e);
		}

		m_textBox->displayText();
	}

	void AnalyticsMenu::displayTotalInformation()
	{
		try {
			std::vector<std::string> displayText;

			displayText = applyAnalyticsCriterion();

			m_textBox->setContent(displayText);
		}
		catch (const std::runtime_error& e) {
			handleFatalErrorMSG(e);
		}

		m_textBox->displayText();
	}

	bool AnalyticsMenu::isLocalTeamCriterion() {
		return m_currentAnalysticsCriterion == AnalyticsCriterion::AverageTeamStats ||
			m_currentAnalysticsCriterion == AnalyticsCriterion::FindPlayer;
	}

	Text AnalyticsMenu::generateFileSelectionMessage()
	{
		return {
		"========================================",
		"      PLEASE SELECT THE APPROPRIATE     ",
		"       TEAM TO MEET THIS CRITERION      ",
		"========================================"
		};
	}

	Text AnalyticsMenu::applyAnalyticsCriterion(const std::string& teamname, const TeamDataList& teamDataList)
	{
		if (m_currentAnalysticsCriterion == AnalyticsCriterion::AverageTeamStats) {
			return hanleAverageTeamStatsCriterion(teamname, teamDataList);
		}
		else if (m_currentAnalysticsCriterion == AnalyticsCriterion::FindPlayer) {
			return hanleFindPlayerCriterion(teamname);
		}
		return Text();
	}

	Text AnalyticsMenu::applyAnalyticsCriterion()
	{
		if (m_currentAnalysticsCriterion == AnalyticsCriterion::AverageOverallStats) {
			return handleAverageOverallStatsCriterion();
		}
		else if (m_currentAnalysticsCriterion == AnalyticsCriterion::YoungestTeam) {
			return hanleYoungestTeamCriterion();
		}
		else if (m_currentAnalysticsCriterion == AnalyticsCriterion::HighestTeam) {
			return hanleHighestTeamCriterion();
		}
		return Text();
	}

	Text AnalyticsMenu::hanleAverageTeamStatsCriterion(
		const std::string& teamname,
		const TeamDataList& teamDataList)
	{
		const core::Team& team = core::utils::textToTeam(teamname, teamDataList);

		double averageAge = core::utils::averageAgeOfTeam(team);
		double averageHeight = core::utils::averageHeightOfTeam(team);
		double averageWeight = core::utils::averageWeightOfTeam(team);

		std::ostringstream stream;
		stream << std::fixed << std::setprecision(2);

		Text resultText;
		resultText.push_back("           TEAM AVERAGE STATS           ");
		resultText.push_back("========================================");

		stream << "Team: " << teamname;
		resultText.push_back(stream.str());
		stream.str(""); stream.clear();

		stream << "Age: " << averageAge << " years";
		resultText.push_back(stream.str());
		stream.str(""); stream.clear();

		stream << "Height: " << averageHeight << " cm";
		resultText.push_back(stream.str());
		stream.str(""); stream.clear();

		stream << "Weight: " << averageWeight << " kg";
		resultText.push_back(stream.str());

		return resultText;
	}

	Text AnalyticsMenu::handleAverageOverallStatsCriterion()
	{
		auto teams = m_appCore.getTeams();

		double averageOverallAge = 0.0;
		double averageOverallHeight = 0.0;
		double averageOverallWeight = 0.0;

		for (const auto& teamname : teams) {
			TeamDataList teamDataList = m_appCore.getTeam(teamname);
			const core::Team& team = core::utils::textToTeam(teamname, teamDataList);

			averageOverallAge += core::utils::averageAgeOfTeam(team);
			averageOverallHeight += core::utils::averageHeightOfTeam(team);
			averageOverallWeight += core::utils::averageWeightOfTeam(team);
		}

		if (!teams.empty()) {
			averageOverallAge /= teams.size();
			averageOverallHeight /= teams.size();
			averageOverallWeight /= teams.size();
		}

		std::ostringstream stream;
		stream << std::fixed << std::setprecision(2);

		Text resultText;
		resultText.push_back("        OVERALL AVERAGE STATS         ");
		resultText.push_back("======================================");

		stream << "Teams analyzed: " << teams.size();
		resultText.push_back(stream.str());
		stream.str(""); stream.clear();

		stream << "Age: " << averageOverallAge << " years";
		resultText.push_back(stream.str());
		stream.str(""); stream.clear();

		stream << "Height: " << averageOverallHeight << " cm";
		resultText.push_back(stream.str());
		stream.str(""); stream.clear();

		stream << "Weight: " << averageOverallWeight << " kg";
		resultText.push_back(stream.str());

		return resultText;
	}

	Text AnalyticsMenu::hanleYoungestTeamCriterion()
	{
		Text resultText;
		auto teams = m_appCore.getTeams();
		if (teams.empty())
			return core::utils::teamToLabeledText(resultText);

		std::optional<core::Team> youngestTeam;
		double minAverageAge = 1.0 * INT_MAX;

		for (const auto& teamname : teams) {
			TeamDataList teamDataList = m_appCore.getTeam(teamname);
			const core::Team& team = core::utils::textToTeam(teamname, teamDataList);
			double averageAge = core::utils::averageAgeOfTeam(team);

			if (averageAge != -1.0 && averageAge < minAverageAge) {
				minAverageAge = averageAge;
				youngestTeam = team;
			}
		}

		if (youngestTeam) {
			resultText.push_back("            THE YOUNGEST TEAM         ");
			resultText.push_back("======================================");

			std::string teamName = "            " + youngestTeam->getTeamName() + "        ";
			resultText.push_back(teamName);
			resultText.push_back("======================================");

			auto teamText = core::utils::teamToText(*youngestTeam);
			teamText = core::utils::teamToLabeledText(teamText);
			resultText.insert(resultText.end(), teamText.begin(), teamText.end());
		}

		return resultText;
	}


	Text AnalyticsMenu::hanleHighestTeamCriterion()
	{
		Text resultText;
		auto teams = m_appCore.getTeams();
		if (teams.empty())
			return core::utils::teamToLabeledText(resultText);

		std::optional<core::Team> highestTeam;
		double maxAverageHeight = 1.0 * INT_MIN;

		for (const auto& teamname : teams) {
			TeamDataList teamDataList = m_appCore.getTeam(teamname);
			const core::Team& team = core::utils::textToTeam(teamname, teamDataList);
			double averageHeight = core::utils::averageHeightOfTeam(team);

			if (averageHeight != -1.0 && averageHeight > maxAverageHeight) {
				maxAverageHeight = averageHeight;
				highestTeam = team;
			}
		}

		if (highestTeam)
		{
			resultText.push_back("            THE HIGHEST TEAM         ");
			resultText.push_back("======================================");

			std::string teamName = "            " + highestTeam->getTeamName() + "        ";
			resultText.push_back(teamName);
			resultText.push_back("======================================");

			auto teamText = core::utils::teamToText(*highestTeam);
			teamText = core::utils::teamToLabeledText(teamText);
			resultText.insert(resultText.end(), teamText.begin(), teamText.end());
		}

		return resultText;
	}

	Text AnalyticsMenu::hanleFindPlayerCriterion(const std::string& teamname)
	{
		std::string surname = getSurnameOfFinedPlayer();

		ui::ConsoleManager::getInstance().clearScreen();
		renderAll();

		if (surname.empty()) return generateFileSelectionMessage();

		Text resultText = m_appCore.binarySearch(teamname, surname, [](const core::Player& player, const std::string& surname) {
			return player.getSurname() < surname;
			});
		
		if (resultText.empty()) {
			resultText = m_appCore.binarySearch(teamname, surname, [](const core::Player& player, const std::string& surname) {
				return player.getSurname() > surname;
				});
		}

		if (resultText.empty()) {
			resultText = m_appCore.linearSearch(teamname, surname, [](const core::Player& player, const std::string& surname) {
				return player.getSurname() == surname;
				});
		}
		
		resultText = core::utils::teamToLabeledText(resultText);

		if (resultText.empty()) {
			resultText = {
				"========================================",
				"           PLAYER NOT FOUND            ",
				"========================================",
				" Player with surname '" + surname + "'",
				" was not found in team '" + teamname + "'.",
				"========================================"
			};
		}

		return resultText;
	}

	std::string AnalyticsMenu::getSurnameOfFinedPlayer()
	{
		Window findPlayerMenuFrame(44, 13, 38, 9);
		findPlayerMenuFrame.addWindowName("FIND PLAYER", 1, 0);
		findPlayerMenuFrame.show();

		std::unique_ptr<ui::widgets::EditLine> editLine =
			std::make_unique<ui::widgets::EditLine>(30, 3, 45, 11, 14);
		editLine->setTitle("surname");
		editLine->renderAll();

		ui::ConsoleManager::getInstance().setCursorPosition(45, 15);
		std::cout << char(250) << " Enter the last name of the";
		ui::ConsoleManager::getInstance().setCursorPosition(47, 16);
		std::cout << "player you are looking for";

		ui::ConsoleManager::getInstance().setCursorPosition(45, 18);
		std::cout << char(250) << " To exit press escape";

		ui::ConsoleManager::getInstance().setCursorPosition(45, 20);
		std::cout << char(250) << " To continue press enter";

		while (true) {
			editLine->onRender();
			if (_kbhit())
			{
				int key = _getch();
				if (key == 27) {
					return {};
				}

				if (key == 13 && !editLine->getText().empty()) {
					return editLine->getText();
				}

				if (!std::isdigit(key)) {
					editLine->onUpdate(key);
				}
			}
		}
	}

	void AnalyticsMenu::handleFatalErrorMSG(const std::exception& e) {
		std::unique_ptr<msg::FatalErrorMSG> notificationMSG
			= std::make_unique<msg::FatalErrorMSG>(63, 9);
		notificationMSG->setPosition(28, 10);
		notificationMSG->setTitle(e.what());
		notificationMSG->run();
	}

	void AnalyticsMenu::handleNotification(
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


} // namespace menu