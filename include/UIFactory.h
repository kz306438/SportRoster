#ifndef UI_FACTORY_H
#define UI_FACTORY_H

#include <memory>
#include <stdexcept>
#include "UI.h"
#include "UIType.h"
#include "TUI.h"

namespace ui
{

	class UIFactory final
	{
	public:
        template <typename... Args>
        [[nodiscard]] static std::unique_ptr<UI> createUI(UIType type, Args&&... args)
        {
            switch (type) {
            case UIType::TUI:
                return std::make_unique<TUI>(std::forward<Args>(args)...);
            default:
                throw std::invalid_argument("There is no such type of UI.");
            }
        }

	};

} // namespace ui

#endif // UI_FACTORY_H