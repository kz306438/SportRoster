#ifndef SORT_MENU_H
#define SORT_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"

#include "buttons.h"
#include "UI/Widgets/Slider.h"
#include "UI/Widgets/TextBox.h"

namespace menu
{

	enum class SortKey: std::uint8_t
	{
		Unknown,
		Surname,
		Age,
		Height,
		GameNumber
	};

	enum class SortOrder : std::uint8_t
	{
		Unknown,
		Ascending,
		Descending
	};

	class SortMenu : public Menu
	{
	public:
		explicit SortMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;

	private:
		void init();

		void connectButtons();
		void setupSortKeyButtonsColor();
		void setupSortOrderButtonsColor();
		void renderAll();
		
	private:
		void updateSliderButtonsName();
		void sliderMoveUp();
		void sliderMoveDown();

	private:
		void proccessSortKeyButton();
		void proccessSortOrderButton();

		void updateSortKeyButtons();
		void updateSortOrderButtons();

	private:
		void displayTeam(int indexOfTeam);
		bool applySort(const std::string& teamname, std::vector<std::string>& teamDataList);
		
		void saveSortedTeam();

	private:
		void handleNotification(std::string,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t);

		bool confirmSave();

	private:
		core::ApplicationCore& m_appCore;

	private:
		int	m_sliderShift{};
		int	m_indexOfLastSortedTeam{};
		
		SortKey		 m_currentSortKey;
		SortOrder	 m_currentSortOrder;

		std::vector<std::string> m_dataOfLastSortedTeam;

	private:
		std::unique_ptr<CustomButton> m_PBBack;
		
		std::unique_ptr<PushButton> m_PBSortSurname;
		std::unique_ptr<PushButton> m_PBSortAge;
		std::unique_ptr<PushButton> m_PBSortHeight;
		std::unique_ptr<PushButton> m_PBSortGameNumber;

		std::unique_ptr<PushButton> m_PBAscending;
		std::unique_ptr<PushButton> m_PBDescending;

		std::unique_ptr<ui::widgets::Slider> m_slider;
		std::unique_ptr<ui::widgets::TextBox> m_textBox;

	};

} // namespace menu

#endif // SORT_MENU_H
