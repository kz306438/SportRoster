#include "UI.h"

namespace ui
{
	UI::UI(std::uint16_t width, std::uint16_t height) noexcept
		: m_width(width), m_height(height) {}

	UI::UI(std::uint16_t width, std::uint16_t height, std::string title)
		: m_width(width), m_height(height), m_title(std::move(title)) {}

} // namespace ui