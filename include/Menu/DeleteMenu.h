#ifndef DELETE_MENU_H
#define DELETE_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"
#include "UI/Widgets/Slider.h"

namespace menu
{

	class DeleteMenu : public Menu
	{
	public:
		DeleteMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;

		void renderAll();

	private:
		void init();

		void connectButtons();

	private:
		void deleteTeam(int indexOfTeam);

		bool confirmDelete();
	private:
		void handleNotification(std::string,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t);

		void updateButtonsName();
		void sliderMoveUp();
		void sliderMoveDown();
	private:
		core::ApplicationCore& m_appCore;

	private:
		int m_sliderShift{};
		std::unique_ptr<ui::widgets::Slider> m_slider;
		std::unique_ptr<PushButton> m_PBBack;
	};

} // namespaace menu

#endif DELETE_MENU_H