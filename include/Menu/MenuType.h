#include <cstdint>
#ifndef MENU_TYPE_H
#define MENU_TYPE_H

namespace menu
{
    /**
     * @brief Enum class representing the types of menus in the application.
     *
     * The `MenuType` enum class defines various menu types available in the application. Each menu type
     * corresponds to a different view or section in the user interface (e.g., main menu). The `Unknown` type
     * can be used to represent an unrecognized or undefined menu type.
     */
    enum class MenuType : std::uint8_t
    {
        /**
         * @brief Represents the main menu of the application.
         *
         * This menu typically serves as the entry point or central navigation hub of the application.
         */
        MainMenu,

        /**
         * @brief Represents the menu used for creating new entities.
         *
         * This menu provides options and input fields for creating new items or configurations.
         */
        CreateMenu,


        /**
         * @brief Represents an unknown or undefined menu type.
         *
         * This value is used as a fallback or placeholder when the menu type is not recognized or is unspecified.
         */
        Unknown
    };

} // namespace menu

#endif // MENU_TYPE_H
