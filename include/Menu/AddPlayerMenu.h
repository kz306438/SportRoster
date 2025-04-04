#ifndef ADD_PLAYER_MENU_H
#define ADD_PLAYER_MENU_H

#include "Menu/Menu.h"
#include "Core/ApplicationCore.h"
#include "UI/Widgets/EditLine.h"
#include <memory>
#include <vector>
namespace menu
{

	class AddPlayerMenu : public Menu
	{
	public:
		explicit AddPlayerMenu(core::ApplicationCore& appCore);

	public:
		void onRender() override;
		void onUpdate() override;

	private:
		void init();
		void renderAll();

	private:
		void handleNotification(std::string,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t,
			std::uint16_t);

		void setupEditLines();
		void renderMarker();
		std::pair<int, int> getMarkerPosition() const;

		void handleEnterKey();
		bool hasEmptyEditLine();
		bool teamExist();
		bool isValidInput();

		std::vector<std::string> getPlayerDataList();
	private:
		core::ApplicationCore& m_appCore;

	private:
		std::vector<std::unique_ptr<ui::widgets::EditLine>> m_editLines;
	
	private:
		int indexOfCurrentEditLine{};
		int m_markPosX{};
		int m_markPosY{};
	};

} // namespace menu

#endif // ADD_PLAYER_MENU_H