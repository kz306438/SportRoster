#ifndef MENU_FACTORY_H
#define MENU_FACTORY_H

#include "Menu.h"
#include "MenuType.h"
#include "Core/ApplicationCore.h"
#include <memory>

namespace menu
{
    /**
     * @brief Abstract factory class for creating menu objects.
     *
     * The MenuFactory class defines the common interface for creating different types of menus.
     * Derived classes must implement the createMenu method to return specific menu instances based on the menu type.
     */
    class MenuFactory
    {
    public:
        /**
         * @brief Constructs the MenuFactory with a reference to the ApplicationCore.
         *
         * @param appCore The ApplicationCore instance passed to the Menu objects created by this factory.
         */
        explicit MenuFactory(core::ApplicationCore& appCore)
            : m_appCore(appCore) {}

    public:
        /**
         * @brief Virtual destructor for MenuFactory.
         */
        virtual ~MenuFactory() = default;

    public:
        /**
         * @brief Creates a menu of the specified type.
         *
         * This is a pure virtual function that must be implemented by derived classes.
         * It returns a unique pointer to a specific `Menu` object based on the provided `MenuType`.
         *
         * @param type The type of the menu to create (e.g., main menu, options menu).
         *
         * @return A unique pointer to a `Menu` object of the specified type.
         */
        [[nodiscard]] virtual std::unique_ptr<Menu> createMenu(MenuType type) = 0;

    protected:
        /**
         * @brief The ApplicationCore reference passed to the Menu objects created by this factory.
         */
        core::ApplicationCore& m_appCore;
    };

} // namespace menu

#endif // MENU_FACTORY_H
