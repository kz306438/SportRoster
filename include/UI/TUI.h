#ifndef TUI_H
#define TUI_H

#include "UI.h"
#include "Menu/MenuType.h"
#include "Core/ApplicationCore.h"

namespace ui
{

	class TUI final : public UI
	{
	public:
		TUI(std::uint16_t width, std::uint16_t height, core::ApplicationCore& appCore) noexcept;
		TUI(std::uint16_t width, std::uint16_t height, std::string title, core::ApplicationCore& appCore);
	public:
		void onRender() override;
		void onUpdate() override;
	
		void setMenu(menu::MenuType type);
	private:
		void init();
	private:
		core::ApplicationCore& m_appCore;
	};

} // namespace ui

#endif // TUI_H
