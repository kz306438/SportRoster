#include "Menu/AddPlayerMenu.h"

#include "UI/ConsoleManager.h"

#include "Message/NotificationMSG.h"
#include "Message/FatalErrorMSG.h"

#include "window.h"

#include <conio.h>
#include <array>
#include <cctype>
#include <algorithm>

namespace menu
{

	AddPlayerMenu::AddPlayerMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		init();
	}

	void AddPlayerMenu::onRender()
	{
		m_editLines[indexOfCurrentEditLine]->onRender();
		renderMarker();
	}

	std::pair<int, int> AddPlayerMenu::getMarkerPosition() const {
		constexpr std::array<std::pair<int, int>, 8> positions{ {
			{30,  9}, {30, 12}, {30, 15}, {30, 18},
			{60,  9}, {60, 12}, {60, 20}, {60, 23}
		} };

		return (indexOfCurrentEditLine >= 0 && indexOfCurrentEditLine < positions.size())
			? positions[indexOfCurrentEditLine]
			: std::make_pair(-1, -1);
	}

	void AddPlayerMenu::handleEnterKey()
	{
		if (hasEmptyEditLine()) {
			handleNotification("FILL IN ALL FIELDS!", 69, 9, 25, 10);
		}
		else if (isValidInput() && teamExist()) {
			try {
				m_appCore.addPlayer(
					m_editLines[7]->getText(),
					getPlayerDataList()
				);
			}
			catch (const std::runtime_error& e) {
				std::unique_ptr<msg::FatalErrorMSG> notificationMSG
					= std::make_unique<msg::FatalErrorMSG>(63, 9);
				notificationMSG->setPosition(28, 10);
				notificationMSG->setTitle(e.what());
				notificationMSG->run();
			}
			handleNotification("PLAYER SUCCESSFULLY ADDED!", 69, 9, 25, 10);
			setPendingMenu(MenuType::MainMenu);
		}
	}

	bool AddPlayerMenu::hasEmptyEditLine()
	{
		for (const auto& editLine : m_editLines) {
			if (editLine->getText().empty()) return true;
		}
		return false;
	}

	bool AddPlayerMenu::teamExist()
	{
		const std::vector<std::string> teams = m_appCore.getTeams();
		std::string team = m_editLines[7]->getText();
		for (const auto& elem : teams) {
			if (team == elem)
				return true;
		}
		handleNotification("THERE IS NO TEAM WITH THIS NAME!", 69, 9, 25, 10);
		return false;
	}

	bool AddPlayerMenu::isValidInput()
	{
		static const std::array<std::pair<int (*)(int), const char*>, 7> validators = {
			std::make_pair(::isdigit, "UNCORRECT NAME"),
			std::make_pair(::isdigit, "UNCORRECT SURNAME"),
			std::make_pair(::isalpha, "UNCORRECT AGE"),
			std::make_pair(::isdigit, "UNCORRECT COUNTRY"),
			std::make_pair(::isalpha, "UNCORRECT HEIGHT"),
			std::make_pair(::isalpha, "UNCORRECT WEIGHT"),
			std::make_pair(::isalpha, "UNCORRECT GAME NUMBER")
		};

		if (indexOfCurrentEditLine < 0 || indexOfCurrentEditLine >= validators.size()) {
			return true;
		}

		for (size_t i = 0; i < m_editLines.size(); ++i)
		{
			const auto& text = m_editLines[i]->getText();
			if (i < validators.size() && std::all_of(text.begin(), text.end(), validators[i].first)) {
				handleNotification(validators[i].second, 69, 9, 25, 10);
				return false;
			}
		}
		return true;
	}

	std::vector<std::string> AddPlayerMenu::getPlayerDataList()
	{
		std::vector<std::string> playerDataLIst;
		playerDataLIst.push_back(m_editLines[0]->getText()); // name
		playerDataLIst.push_back(m_editLines[1]->getText()); // surname
		playerDataLIst.push_back(m_editLines[2]->getText()); // age
		playerDataLIst.push_back(m_editLines[4]->getText()); // height
		playerDataLIst.push_back(m_editLines[5]->getText()); // weight
		playerDataLIst.push_back(m_editLines[6]->getText()); // game number
		playerDataLIst.push_back(m_editLines[3]->getText()); // country name
		return playerDataLIst;
	}


	void AddPlayerMenu::renderMarker() {
		auto [markPosX, markPosY] = getMarkerPosition();
		if (markPosX == -1) return;

		if (markPosX != m_markPosX || markPosY != m_markPosY) {
			ui::ConsoleManager::getInstance().setCursorPosition(m_markPosX, m_markPosY);
			std::cout << ' ';
			m_markPosX = markPosX;
			m_markPosY = markPosY;
		}
		ui::ConsoleManager::getInstance().setCursorPosition(markPosX, markPosY);
		std::cout << '*';
	}

	void AddPlayerMenu::onUpdate()
	{
		if (_kbhit())
		{
			int key = _getch();
			if (key == 27) {
				ui::ConsoleManager::getInstance().clearScreen();
				setPendingMenu(MenuType::MainMenu);
			}
			else if (key == '\t') {
				indexOfCurrentEditLine = (indexOfCurrentEditLine + 1) % m_editLines.size();
			}
			else if (key == 13) {
				handleEnterKey();
			}


			m_editLines[indexOfCurrentEditLine]->onUpdate(key);
		}
	}

	void AddPlayerMenu::init()
	{
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 32, 8, 15));
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 32, 11, 15));
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 32, 14, 15));
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 32, 17, 15));
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 62, 8, 15));
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 62, 11, 15));
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 62, 19, 15));
		m_editLines.push_back(std::make_unique<ui::widgets::EditLine>(25, 3, 62, 22, 15));

		setupEditLines();
		renderAll();
	}

	void AddPlayerMenu::renderAll()
	{
		Window mainFrame(63, 26, 28, 2);
		mainFrame.addWindowName("ADD PLAYER", 1, 0);
		mainFrame.show();

		Window personalInformationFrame(27, 15, 31, 6);
		personalInformationFrame.addWindowName("Personal Information", 1, 0);
		personalInformationFrame.show();

		Window physicalAttributesFrame(27, 9, 61, 6);
		physicalAttributesFrame.addWindowName("Physical Attributes", 1, 0);
		physicalAttributesFrame.show();

		Window playerDetails(27, 9, 61, 17);
		playerDetails.addWindowName("Player Details", 1, 0);
		playerDetails.show();

		Window dialogWindow(27, 5, 31, 21);
		dialogWindow.addWindowName("dialog", 1, 0);
		dialogWindow.show();

		ui::ConsoleManager::getInstance().setCursorPosition(35, 22); std::cout << "FILL IN ALL FIELDS!";
		ui::ConsoleManager::getInstance().setCursorPosition(34, 23); std::cout << "TO SAVE, PRESS ENTER!";
		ui::ConsoleManager::getInstance().setCursorPosition(34, 24); std::cout << "TO EXIT PRESS ESCAPE!";

		for (const auto& editLine : m_editLines) {
			editLine->renderAll();
		}
		renderMarker();
	}

	void AddPlayerMenu::handleNotification(std::string title,
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

	void AddPlayerMenu::setupEditLines()
	{
		m_editLines[0]->setTitle("Name");
		m_editLines[1]->setTitle("Surname");
		m_editLines[2]->setTitle("Age");
		m_editLines[3]->setTitle("Country");
		m_editLines[4]->setTitle("Height");
		m_editLines[5]->setTitle("Weight");
		m_editLines[6]->setTitle("Game number");
		m_editLines[7]->setTitle("Team name");
	}

} // namespace menu