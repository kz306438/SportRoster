#include "UI/Widgets/EditLine.h"
#include "UI/ConsoleManager.h"

#include "Window.h"

namespace ui::widgets
{

	EditLine::EditLine(std::uint16_t width, std::uint16_t height, std::size_t capacity) noexcept
		: m_width(width), m_height(height), m_capacity(capacity) {}

	EditLine::EditLine(std::uint16_t width, std::uint16_t height, std::uint16_t posX, std::uint16_t posY, std::size_t capacity) noexcept
		: m_width(width), m_height(height), m_posX(posX), m_posY(posY), m_capacity(capacity) {}

	void EditLine::onRender()
	{
		displayText();
		displayCursor();
	}

	void EditLine::onUpdate(int key)
	{
		handleInput(key);
	}

	void EditLine::renderAll() {

		Window wnd(m_width, m_height, m_posX, m_posY);
		wnd.addWindowName("edit line", 3, 0);
		wnd.show();

		displayText();
		displayCursor();
	}



	std::string EditLine::getText() const {
		return m_text;
	}

	void EditLine::handleInput(int key) {
		if (key == 75) {
			if (m_curPos > 0) m_curPos--;
		}
		else if (key == 77) {
			if (m_curPos < m_text.length()) m_curPos++;
		}
		else if (key == 8) {
			if (m_curPos > 0) {
				m_text.erase(m_curPos - 1, 1);
				m_curPos--;
			}
		}
		else if (isValidCharacter(key)) {
			handleInsertCharacter(key);
		}
	}

	void EditLine::handleInsertCharacter(int key)
	{
		if (m_text.length() < m_capacity)
		{
			m_text.insert(m_curPos, 1, (char)key);
			m_curPos++;
		}
	}

	void EditLine::displayCursor() const
	{
		ConsoleManager::getInstance().saveConsoleAttributes();
		ConsoleManager::getInstance().setColorBackground(White);
		ConsoleManager::getInstance().setColorForeground(Black);

		ConsoleManager::getInstance().setCursorPosition(m_curPos + m_posX + 2, m_posY + 1);
		std::cout << ' ';
		ConsoleManager::getInstance().setCursorPosition(m_curPos + m_posX + 2, m_posY + 1);


		ConsoleManager::getInstance().restoreConsoleAttributes();
	}

	void EditLine::displayText() const
	{
		ConsoleManager::getInstance().setCursorPosition(m_posX + 2, m_posY + 1);
		std::cout << m_text;
	}

	bool EditLine::isValidCharacter(int key) const {
		return std::isalpha(key) || std::isspace(key) || std::isdigit(key) || key == '_';
	}

} // namespace ui::widgets