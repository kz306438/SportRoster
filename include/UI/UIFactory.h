#ifndef UI_FACTORY_H
#define UI_FACTORY_H

#include <memory>
#include <stdexcept>
#include "UI.h"
#include "UIType.h"
#include "TUI.h"

namespace ui
{
    /**
     * @brief A factory class for creating instances of different types of UIs.
     *
     * This class is responsible for creating user interface (UI) objects based on the specified
     * `UIType`. It provides a static method to create and return a `std::unique_ptr` to the appropriate
     * UI instance, such as a `TUI` (Text-based User Interface).
     */
    class UIFactory final
    {
    public:
        /**
         * @brief Creates a UI object based on the specified type.
         *
         * This method checks the provided `UIType` and creates the corresponding UI object.
         * If the type is `UIType::TUI`, a `TUI` instance will be created. If an unknown type is
         * provided, an exception is thrown.
         *
         * @tparam Args The types of arguments to be forwarded to the UI constructor.
         * @param type The type of UI to create (e.g., `UIType::TUI`).
         * @param args Additional arguments to pass to the UI constructor.
         * @return std::unique_ptr<UI> A unique pointer to the created UI object.
         * @throws std::invalid_argument If the specified UI type is unsupported.
         */
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
