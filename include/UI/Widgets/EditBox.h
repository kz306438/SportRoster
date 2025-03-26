#ifndef EDIT_BOX_H
#define EDIT_BOX_H

#include <vector>
#include <string>
#include <memory>

#include "GUI.h"

namespace ui::widgets
{
	
	using Content = std::vector<std::string>;

	class EditBox
	{
	public:
		EditBox(std::uint16_t width,
			std::uint16_t height,
			std::uint16_t posX,
			std::uint16_t posY);

	public:
		void onUpdate(int key);

		void renderAll();

	public:
		void setContent(Content content);
		void display();

	private:
		void init();

	private:
		void displayCursor();

		void moveUp();
		void moveDown();

	private:
		void handleBackspace();
		void handleInsert(int key);

	private:
		Content m_content;
		int m_shift{};

	private:
		std::uint16_t m_cursorPosX{};
		std::uint16_t m_cursorPosY{};

	private:
		std::uint16_t m_width{};
		std::uint16_t m_height{};
		std::uint16_t m_posX{};
		std::uint16_t m_posY{};
	};

} // namespace ui::widgets

#endif // EDIT_BOX_H
