#ifndef UI_FACTORY_H
#define UI_FACTORY_H

#include <memory>
#include "UI.h"

namespace ui
{
	enum class UIType : std::uint16_t
	{
		TUI,
		Unknown
	};

	class UIFactory final
	{
	public:
		[[nodiscard]] static std::unique_ptr<UI> createUI(UIType type);
	};

} // namespace ui

#endif // UI_FACTORY_H