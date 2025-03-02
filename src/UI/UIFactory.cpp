#include "UIFactory.h"

#include <stdexcept>
#include "TUI.h"

namespace ui
{

	std::unique_ptr<UI> UIFactory::createUI(UIType type)
	{
		if (type == UIType::TUI) {
			return std::make_unique<TUI>();
		}
		else {
			throw std::invalid_argument("There is no such type of UI.");
		}
	}
} // namespace ui