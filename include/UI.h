#ifndef UI_H
#define UI_H

#include <string>

namespace ui
{
	class UI
	{
	public:
		virtual ~UI() = default;
		
	public:
		UI() = default;
		UI(std::uint16_t width, std::uint16_t height) noexcept;
		UI(std::uint16_t width, std::uint16_t height, std::string title);

	public:
		virtual void onRender() = 0;
		virtual void onUpdate() = 0;

	protected:
		std::string m_title;
		std::uint16_t m_width{};
		std::uint16_t m_height{};
	};

} // namespace ui

#endif // UI_H
