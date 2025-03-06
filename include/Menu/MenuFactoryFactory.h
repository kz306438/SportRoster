#ifndef MENU_FACTORY_FACTORY_H
#define MENU_FACTORY_FACTORY_H

#include "MenuFactory.h"
#include "TUIMenuFactory.h"
#include "UI/UIType.h"
#include "Core/ApplicationCore.h"
#include <memory>
#include <stdexcept>

namespace menu
{
    /**
     * @brief Factory class for creating different types of MenuFactory objects.
     *
     * The MenuFactoryFactory class is responsible for creating specific instances of the MenuFactory,
     * depending on the UI type (such as TUI). It ensures that the appropriate MenuFactory is instantiated
     * based on the provided UI type.
     */
    class MenuFactoryFactory final
    {
    public:
        /**
         * @brief Constructs the MenuFactoryFactory with an ApplicationCore instance.
         *
         * @param appCore The ApplicationCore instance to be passed to the MenuFactory objects.
         */
        explicit MenuFactoryFactory(core::ApplicationCore& appCore)
            : m_appCore(appCore) {}

    public:
        /**
         * @brief Creates a MenuFactory based on the provided UI type.
         *
         * This method instantiates the correct MenuFactory implementation based on the UIType.
         *
         * @param type The type of UI (e.g., TUI).
         * @param appCore The ApplicationCore instance that will be passed to the MenuFactory.
         *
         * @return A unique pointer to the appropriate MenuFactory.
         *
         * @throws std::invalid_argument If the UI type does not have a corresponding MenuFactory.
         */
        [[nodiscard]] static std::unique_ptr<MenuFactory> createMenuFactory(ui::UIType type, core::ApplicationCore appCore)
        {
            if (type == ui::UIType::TUI) {
                return std::make_unique<TUIMenuFactory>(appCore);
            }
            else {
                throw std::invalid_argument("There is no such type of UI.");
            }
        }

    private:
        /**
         * @brief The ApplicationCore instance passed to the MenuFactory objects.
         */
        core::ApplicationCore m_appCore;
    };

} // namespace menu

#endif // MENU_FACTORY_FACTORY_H
