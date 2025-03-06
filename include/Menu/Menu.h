#ifndef MENU_H
#define MENU_H

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
    };

} // namespace menu

#endif // MENU_H
