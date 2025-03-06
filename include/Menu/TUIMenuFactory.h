#ifndef TUI_MENU_FACTORY_H
#define TUI_MENU_FACTORY_H

#include "MenuFactory.h"
#include "MenuType.h"
#include "Core/ApplicationCore.h"

namespace menu
{
    /**
     * @brief Concrete factory class for creating TUI (Text User Interface) menus.
     *
     * The TUIMenuFactory class is a concrete implementation of the MenuFactory, responsible for creating
     * TUI-specific menu objects based on the provided `MenuType`. This class overrides the `createMenu`
     * method to return the appropriate TUI menu objects.
     */
    class TUIMenuFactory final : public MenuFactory
    {
    public:
        /**
         * @brief Constructs the TUIMenuFactory with a reference to the ApplicationCore.
         *
         * @param appCore The ApplicationCore instance passed to the TUI menu objects created by this factory.
         */
        explicit TUIMenuFactory(core::ApplicationCore& appCore)
            : MenuFactory(appCore) {}

    public:
        /**
         * @brief Creates a TUI menu of the specified type.
         *
         * This method overrides the base `createMenu` method to create a menu tailored for the TUI. It
         * returns a unique pointer to a `Menu` object based on the provided `MenuType` (such as main menu,
         * settings menu, etc.).
         *
         * @param type The type of menu to create (e.g., main menu, settings menu).
         *
         * @return A unique pointer to the appropriate `Menu` object for TUI.
         */
        [[nodiscard]] std::unique_ptr<Menu> createMenu(MenuType type) override;
    };

} // namespace menu

#endif // TUI_MENU_FACTORY_H
