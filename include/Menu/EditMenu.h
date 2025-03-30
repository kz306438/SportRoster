#ifndef EDIT_MENU_H
#define EDIT_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"
#include "UI/Widgets/EditBox.h"
#include "UI/Widgets/Slider.h"
#include "buttons.h"

namespace menu
{

	class EditMenu : public Menu
	{
	public:
		EditMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;

	private:
		void init();

	private:
		void editTeam(int indexOfTeam);

		void handleEditLoop();
		void displayError(const std::string& errorMessage);
		void saveTeamData(const std::string& teamName, const std::vector<std::string>& resultText);
		bool confirmSave();

		void cleanFileLines(std::vector<std::string>& lines);
	
	private:
		void renderAll();

	private:
		void renderEditMenu();
		void connectButtons();
		
	private:
		void updateSliderButtonsName();
		void sliderMoveUp();
		void sliderMoveDown();
	
	private:
		int m_sliderShift{};

	private:
		core::ApplicationCore& m_appCore;
		
	private:
		std::unique_ptr<PushButton> m_PBBack;
		std::unique_ptr<ui::widgets::Slider> m_slider;
		std::unique_ptr<ui::widgets::EditBox> m_editBox;
	};

} // namespace menu

#endif // EDIT_MENU_H
