#include "UI/Widgets/EditBox.h"

#include "UI/ConsoleManager.h"

namespace ui::widgets
{
	EditBox::EditBox(std::uint16_t width
		, std::uint16_t height
		, std::uint16_t posX
		, std::uint16_t posY)
		: m_width(width)
		, m_height(height)
		, m_posX(posX)
		, m_posY(posY)
	{
		init();
	}

	void EditBox::onRender()
	{
		displayCursor();
	}

	void EditBox::onUpdate(int key)
	{
		if (key == 224) { // Arrow keys
			
			key = _getch();

			switch (key) {
			case 72: // Up arrow
				if (m_cursorPosY > 0)
					m_cursorPosY--;
				else
					moveUp();
				break;
			case 80: // Down arrow
				if (m_cursorPosY < m_height - 3)
					m_cursorPosY++;
				else
					moveDown();
				break;
			case 75: // Left arrow
				if (m_cursorPosX > 0) m_cursorPosX--;
				break;
			case 77: // Right arrow
				if (m_cursorPosX < m_width - 3) m_cursorPosX++;
				break;
			}
		}
		else if (key == 8) { // Backspace
			handleBackspace();
		}
		else if (key >= 32 && key <= 126) { // Printable characters
			handleInsert(key);
		}
		displayText();
	}

	void EditBox::renderAll()
	{
		Window editBoxFrame(m_width, m_height, m_posX, m_posY);
		editBoxFrame.addWindowName("edit box", 1, 0);
		editBoxFrame.show();

		displayText();
		displayCursor();
	}

	void EditBox::setContent(const Content& content)
	{
		m_shift = 0;
		m_content.clear();
		m_content.resize(content.size());

		for (size_t i = 0; i < content.size(); i++) {

			if (content[i].size() >= m_width - 2) {
				m_content[i] = content[i];
			}
			else {
				m_content[i] = content[i] + std::string(m_width - 2 - content[i].size(), ' ');
			}
		}
	}

	Content EditBox::getContent() {
		return m_content;
	}

	void EditBox::displayCursor()
	{
		saveConsoleAttributes();
		setColorBackground(White);
		setColorForeground(Black);

		ui::ConsoleManager::getInstance().setCursorPosition(m_posX + m_cursorPosX + 1, m_posY + m_cursorPosY + 1);
		
		if(m_content.size() > m_cursorPosY && m_content[0].size() > m_cursorPosX) {
			std::cout << m_content[m_cursorPosY + m_shift][m_cursorPosX];
		}
		restoreConsoleAttributes();
	}

	void EditBox::moveUp()
	{
		if (m_shift > 0)
			m_shift--;
	}

	void EditBox::moveDown()
	{
		if (m_content.size() - m_shift > m_height - 2)
			m_shift++;
	}

	void EditBox::handleBackspace()
	{
		if (m_cursorPosX > 0) {
			m_content[m_cursorPosY + m_shift].erase(m_cursorPosX - 1, 1);
			m_content[m_cursorPosY + m_shift] += ' ';
			m_cursorPosX--;
		}
	}

	void EditBox::handleInsert(int key)
	{
		if (m_cursorPosY >= 0 && m_cursorPosY < m_content.size()) {
			m_content[m_cursorPosY + m_shift].insert(m_cursorPosX, 1, key);
			if (m_cursorPosX < m_width - 3)
				m_cursorPosX++;
		}
	}

	void EditBox::displayText()
	{
		for (int i = 1; i < m_height - 1; i++) {
			ui::ConsoleManager::getInstance().setCursorPosition(m_posX + 1, m_posY + i);

			if (i - 1 + m_shift < m_content.size()) {
				std::string line = m_content[i - 1 + m_shift];
				std::cout << line.substr(0, m_width - 2);
			}
			else {
				std::cout << std::string(m_width - 2, ' ');
			}
		}
	}


	void EditBox::init()
	{
		m_cursorPosX = 0;
		m_cursorPosY = 0;
	}

} // namespace ui::widgets