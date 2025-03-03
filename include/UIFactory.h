#ifndef UI_FACTORY_H
#define UI_FACTORY_H

#include <memory>
#include "UI.h"
#include "UIType.h"

namespace ui
{

	class UIFactory final
	{
	public:
		[[nodiscard]] static std::unique_ptr<UI> createUI(UIType type);
	};

} // namespace ui

#endif // UI_FACTORY_H