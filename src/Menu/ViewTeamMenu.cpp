#include "Menu/ViewTeamMenu.h"

#include "UI/ConsoleManager.h"
#include "Message/FatalErrorMSG.h"
#include "Core/Utils.h"
#include "window.h"

namespace menu
{

	ViewTeamMenu::ViewTeamMenu(core::ApplicationCore& appCore)
		: m_appCore(appCore)
	{
		init();
	}

	void ViewTeamMenu::onRender()
	{
		m_slider->onRender();
		m_textBox->onRender();
		m_PBBack->allowChanges(); m_PBBack->show();
	}

	void ViewTeamMenu::onUpdate()
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
			m_PBBack.get()
		);
	}

	void ViewTeamMenu::init() {
		m_PBBack	 = std::make_unique<PushButton>(20, 5, "BACK", 87, 4);
		m_slider	 = std::make_unique<ui::widgets::Slider>(5, 20, 3, 15, 5);	
		m_textBox	 = std::make_unique<ui::widgets::TextBox>(40, 21, 40, 5);	

		m_PBBack->setBackgroundColor(White);
		m_PBBack->setForegroundColor(Black);

		connectButtons();
		updateSliderButtonsName();

		Window mainFrame(69, 24, 13, 3);
		mainFrame.addWindowName("VIEW TEAM", 1, 0);
		mainFrame.show();

		m_textBox->renderAll();
	}

	void ViewTeamMenu::viewTeam(int indexOfTeam)
	{	
		const auto teams = m_appCore.getTeams();
		if (indexOfTeam >= teams.size()) return;

		try {
			m_textBox->setContent(core::utils::teamToLabeledText(m_appCore.getTeam(teams[indexOfTeam])));
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

	void ViewTeamMenu::connectButtons()
	{
		m_PBBack->connect([&]() {
			ui::ConsoleManager::getInstance().clearScreen();
			setPendingMenu(MenuType::MainMenu);
			});

		auto& sliderButtons = m_slider->getButtons();

		sliderButtons[0]->connect([&]() { sliderMoveUp(); updateSliderButtonsName(); });

		for (int i = 1; i < sliderButtons.size() - 1; ++i) {
			int indexOfTeam = i - 1;
			sliderButtons[i]->connect([this, indexOfTeam]() {
				this->viewTeam(indexOfTeam + this->m_sliderShift);
				});
		}

		sliderButtons[m_slider->capacity() - 1]->connect([&]() { sliderMoveDown(); updateSliderButtonsName(); });

		auto& textBoxUpButton = m_textBox->getUpButton();
		auto& textBoxDownButton = m_textBox->getDownButton();

		textBoxUpButton->connect([&]() { m_textBox->moveUp(); m_textBox->displayText(); });
		textBoxDownButton->connect([&]() { m_textBox->moveDown(); m_textBox->displayText(); });
	}

	void ViewTeamMenu::updateSliderButtonsName()
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

	void ViewTeamMenu::sliderMoveUp()
	{
		if (m_sliderShift > 0)
			m_sliderShift--;
	}

	void ViewTeamMenu::sliderMoveDown()
	{
		if (m_sliderShift + m_slider->capacity() - 2 < m_appCore.getTeams().size())
			m_sliderShift++;
	}

} // namespace menu