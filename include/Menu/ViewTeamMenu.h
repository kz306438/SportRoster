#ifndef VIEW_TEAM_MENU_H
#define VIEW_TEAM_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"

#include "UI/Widgets/Slider.h"
#include "UI/Widgets/TextBox.h"

namespace menu
{

	class ViewTeamMenu : public Menu
	{
	public:
		explicit ViewTeamMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;

	private:
		void init();
		void connectButtons();

	private:
		void viewTeam(int indexOfTeam);

	private:
		void updateSliderButtonsName();
		void sliderMoveUp();
		void sliderMoveDown();

	private:
		int m_sliderShift{};
	
	private:
		core::ApplicationCore& m_appCore;

	private:
		std::unique_ptr<CustomButton> m_CBBack;
		std::unique_ptr<ui::widgets::Slider> m_slider;
		std::unique_ptr<ui::widgets::TextBox> m_textBox;
	};

} // namespace menu

#endif // VIEW_TEAM_MENU_H
