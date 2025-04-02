#ifndef MENU_H
#define MENU_H

#include <functional>
#include <memory>
#include "Menu/MenuType.h"

namespace menu
{
    /**
     * @brief Abstract base class representing a menu in the application.
     *
     * The `Menu` class is the base class for all menu types in the application. It provides the
     * interface for rendering and updating the menu. Derived classes must implement these methods
     * to define specific behavior for different menus.
     */
    class Menu
    {
    public:
        /**
         * @brief Virtual destructor for proper cleanup of derived classes.
         */
        virtual ~Menu() = default;

    public:
        /**
         * @brief Renders the menu, displaying it on the screen.
         *
         * Derived classes should implement this method to define how the menu should be displayed.
         */
        virtual void onRender() = 0;

        /**
         * @brief Updates the menu state, handling user input or other logic.
         *
         * Derived classes should implement this method to define how the menu responds to user actions
         * or other system events.
         */
        virtual void onUpdate() = 0;    

        /**
         * @brief Sets the pending menu to be displayed.
         *
         * This method updates the menu that is pending to be shown in the next cycle or update.
         *
         * @param newMenu The type of the new menu to be set as pending.
         */
        void setPendingMenu(MenuType newMenu) { m_pendingMenu = newMenu; }

        /**
         * @brief Retrieves the currently pending menu.
         *
         * This method returns the type of the menu that is set to be shown next.
         *
         * @return The type of the pending menu.
         */
        MenuType getPendingMenu() const { return m_pendingMenu; }

    private:
        /**
         * @brief The type of the pending menu.
         *
         * This member stores the type of the menu that is pending and will be displayed next.
         * The default value is `MenuType::Unknown` until set by `setPendingMenu()`.
         */
        MenuType m_pendingMenu = MenuType::Unknown;

    };

} // namespace menu

#endif // MENU_H
