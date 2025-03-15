#ifndef WIDGETS_EDIT_LINE_H
#define WIDGETS_EDIT_LINE_H

#include <string>

namespace ui::widgets
{

	class EditLine
	{
	public:

		EditLine() = default;
		EditLine(std::uint16_t width, std::uint16_t height, std::size_t capacity) noexcept;
		EditLine(std::uint16_t width, std::uint16_t height, std::uint16_t posX, std::uint16_t posY, std::size_t capacity) noexcept;
		
	public:
		void onRender();
		void onUpdate(int key);

		void renderAll();

	public:
		void setTitle(const std::string& title);

		std::string getText() const;

	private:
		void init();

	private:
		void handleInput(int key);
		void handleInsertCharacter(int key);

		void displayCursor() const;
		void displayText() const;

		bool isValidCharacter(int key) const; 

	private:
		std::uint16_t m_width{};
		std::uint16_t m_height{};
		std::uint16_t m_posX{};
		std::uint16_t m_posY{};
		
		std::uint16_t m_curPos{};

		std::size_t m_capacity{};
	private:
		std::string m_title;
		std::string m_text;

	private:
		bool m_needRender = true;

	};

} // namespace ui::widgets

#endif WIDGETS_EDIT_LINE_H