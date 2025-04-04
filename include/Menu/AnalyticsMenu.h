#ifndef ANALYTICS_MENU_H
#define ANALYTICS_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"

#include "UI/Widgets/TextBox.h"
#include "UI/Widgets/Slider.h"
#include "buttons.h"

namespace menu
{
	using Text = std::vector<std::string>;
	using TeamDataList = std::vector<std::string>;

	enum class AnalyticsCriterion : std::uint8_t
	{
		Unknown,
		AverageTeamStats,
		AverageOverallStats,
		YoungestTeam,
		HighestTeam,
		FindPlayer
	};

	class AnalyticsMenu : public Menu
	{
	public:
		explicit AnalyticsMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;

	private:
		void init();

		void connectButtons();
		void setupAnalyticsButtonsColor();
		void renderAll();

		void proccessAnalyticsButtons();

	private:
		void updateSliderButtonsName();
		void sliderMoveUp();
		void sliderMoveDown();

	private:
		void defaultDisplay(int indexOfTeam);
		void displayTotalInformation();

		bool isLocalTeamCriterion();
		Text generateFileSelectionMessage();

		Text applyAnalyticsCriterion(const std::string& teamname,
									const TeamDataList& teamDataList);
		Text applyAnalyticsCriterion();

		Text hanleAverageTeamStatsCriterion(
			const std::string& teamname,
			const TeamDataList& teamDataList);
		
		Text handleAverageOverallStatsCriterion();
		
		Text hanleYoungestTeamCriterion();
		Text hanleHighestTeamCriterion();

		Text hanleFindPlayerCriterion(const std::string& teamname);

		std::string getSurnameOfFinedPlayer();

	private:
		void handleFatalErrorMSG(const std::exception& e);
		
		void handleNotification(std::string,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t);

	private:
		core::ApplicationCore& m_appCore;
	
	private:
		int	m_sliderShift{};
		AnalyticsCriterion m_currentAnalysticsCriterion;

	private:
		std::unique_ptr<ui::widgets::Slider> m_slider;
		std::unique_ptr<ui::widgets::TextBox> m_textBox;

		std::unique_ptr<PushButton> m_PBAverageTeamStats;
		std::unique_ptr<PushButton> m_PBAverageOverallStats;
		
		std::unique_ptr<PushButton> m_PBYoungestTeam;
		std::unique_ptr<PushButton> m_PBHighestTeam;

		std::unique_ptr<PushButton> m_PBFindPlayer;

		std::unique_ptr<CustomButton> m_CBBack;	
	};

} // namespace menu

#endif ANALYTICS_MENU_H