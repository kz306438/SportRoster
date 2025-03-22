#include "UI/Widgets/TextBox.h"

#include "window.h"
#include "UI/ConsoleManager.h"

namespace ui::widgets
{

	TextBox::TextBox(std::uint16_t width,
		std::uint16_t height)
		: m_width(width)
		, m_height(height)
	{
		init();
	}

	TextBox::TextBox(std::uint16_t width
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

	void TextBox::onRender()
	{
		m_PBUp->allowChanges(); m_PBUp->show();
		m_PBDown->allowChanges(); m_PBDown->show();
	}

	void TextBox::onUpdate()
	{
		mouseButtonInteraction(m_PBUp.get(), m_PBDown.get());
	}

	void TextBox::renderAll()
	{
		Window contentFrame(m_width, m_height - 2 * MIN_ELEMENT_HEIGHT, m_posX, m_posY + MIN_ELEMENT_HEIGHT);
		contentFrame.show();
	}

	std::unique_ptr<PushButton>& TextBox::getUpButton() {
		return m_PBUp;
	}

	std::unique_ptr<PushButton>& TextBox::getDownButton() {
		return m_PBDown;
	}

	void TextBox::setContent(const Content& content) {
		m_content.clear();
		m_content.resize(content.size());

		for (size_t i = 0; i < content.size(); i++) {
			
			std::string str(' ', m_width - 2);

			for (size_t j = 0; j < m_width - 2; j++) {
				str[j] = (j < content[i].size())? content[i][j] : ' ';
			}
			m_content[i] = str;
		}

		m_content = content;
	}

	void TextBox::displayText() {
		for (int i = 1; i < m_height - 2 * MIN_ELEMENT_HEIGHT - 1; i++) {
			ui::ConsoleManager::getInstance().setCursorPosition(m_width + 1, m_posY + MIN_ELEMENT_HEIGHT + i);
			std::cout << m_content[i - 1];
		}
	}

	void TextBox::init()
	{
		if (m_width < MIN_ELEMENT_HEIGHT) m_width = MIN_ELEMENT_WIDTH;
		if (m_height < MIN_ELEMENT_HEIGHT) m_height = MIN_ELEMENT_HEIGHT;

		const std::string sym_up(1, char(30));
		const std::string sym_down(1, char(31));

		m_PBUp = std::make_unique<PushButton>(m_width, MIN_ELEMENT_WIDTH, sym_up, m_posX, m_posY);
		m_PBUp = std::make_unique<PushButton>(m_width, MIN_ELEMENT_WIDTH, sym_down, m_posX, m_posY + m_height - MIN_ELEMENT_HEIGHT);

		m_PBUp->setBackgroundColor(BrightRed);
		m_PBUp->setForegroundColor(Black);

		m_PBDown->setBackgroundColor(BrightRed);
		m_PBDown->setForegroundColor(Black);
	}

} // namespace ui::widgets