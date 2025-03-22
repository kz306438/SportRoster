#include "UI/Widgets/Slider.h"

namespace ui::widgets
{



	Slider::Slider(std::uint16_t capacity)
		: m_capacity(capacity)
		, m_buttonWidth(20)
		, m_buttonHeight(3)
	{
		init();
	}

	Slider::Slider(
		std::uint16_t capacity,
		std::uint16_t buttonWidth,
		std::uint16_t buttonHeight)
		: m_capacity(capacity)
		, m_buttonWidth(buttonWidth)
		, m_buttonHeight(buttonHeight)
	{
		init();
	}

	widgets::Slider::Slider(
		std::uint16_t capacity,
		std::uint16_t buttonWidth,
		std::uint16_t buttonHeight,
		std::uint16_t posX,
		std::uint16_t posY)
		: m_capacity(capacity)
		, m_buttonWidth(buttonWidth)
		, m_buttonHeight(buttonHeight)
		, m_posX(posX)
		, m_posY(posY)
	{
		init();
	}

	std::vector<std::unique_ptr<PushButton>>& widgets::Slider::getButtons() {
		return m_buttons;
	}

	int widgets::Slider::capacity() {
		return m_capacity;
	}

	void Slider::init()
	{
		// fix size
		if (m_buttonWidth < 3) m_buttonWidth = 3;
		if (m_buttonHeight < 3) m_buttonHeight = 3;
		m_capacity += 2; // with arrow-buttons

		const std::string sym_up(1, char(30));
		const std::string sym_down(1, char(31));

		// create buttons
		m_buttons.push_back(std::make_unique<PushButton>(
			m_buttonWidth,
			m_buttonHeight, 
			sym_up,
			m_posX,
			m_posY
		));
		
		int i = 0;
		for (; i < m_capacity - 2; i++) {
			m_buttons.push_back(
				std::make_unique<PushButton>(
					m_buttonWidth, m_buttonHeight, "", m_posX, m_posY + m_buttonHeight * (i + 1)
				)
			);
		}

		m_buttons.push_back(std::make_unique<PushButton>(
			m_buttonWidth,
			m_buttonHeight,
			sym_down,
			m_posX,
			m_posY + m_buttonHeight * (i + 1)
		));

		// colorize buttons
		m_buttons[0]->setBackgroundColor(BrightRed);
		m_buttons[0]->setForegroundColor(Black);
	
		for (size_t i = 1; i < m_buttons.size() - 1; ++i) {
			m_buttons[i]->setBackgroundColor(White);
			m_buttons[i]->setForegroundColor(Black);
		}

		m_buttons[m_capacity - 1]->setBackgroundColor(BrightRed);
		m_buttons[m_capacity - 1]->setForegroundColor(Black);
	}

} // namespace ui::widgets