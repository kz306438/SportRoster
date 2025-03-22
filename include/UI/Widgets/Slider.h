#ifndef WIDGET_SLIDER_H
#define WIDGET_SLIDER_H

#include <vector>
#include "buttons.h"

namespace ui::widgets
{

	class Slider
	{
	public:
		Slider(std::uint16_t capacity);
		Slider(std::uint16_t capacity, std::uint16_t buttonWidth, std::uint16_t buttonHeight);
		Slider(std::uint16_t capacity, std::uint16_t buttonWidth, std::uint16_t buttonHeight, std::uint16_t posX, std::uint16_t posY);

	public:

		[[nodiscard]] std::vector<std::unique_ptr<PushButton>>& getButtons();
		[[nodiscard]] int capacity();

	private:
		void init();

	private:
		std::uint16_t m_buttonWidth{};
		std::uint16_t m_buttonHeight{};

		std::uint16_t m_posX{};
		std::uint16_t m_posY{};

	protected:
		int m_capacity{};
		std::vector<std::unique_ptr<PushButton>> m_buttons;
	};

} // namespace ui::widgets

#endif WIDGET_SLIDER_H