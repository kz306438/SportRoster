#ifndef UI_H
#define UI_H

#include <string>
#include <memory>
#include <functional>
#include "Menu/MenuType.h"
#include "Menu/MenuFactory.h"

namespace ui
{
    /**
     * @brief Abstract base class representing a User Interface (UI).
     *
     * This class serves as the base for different types of user interfaces, providing common
     * functionality and properties such as width, height, title, and a menu. Derived classes
     * must implement the `onRender` and `onUpdate` methods to handle specific rendering and
     * updating behavior.
     */
    class UI
    {
    public:
        virtual ~UI() = default;

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes the UI with default values for width, height, and title.
         */
        UI() = default;

        /**
         * @brief Constructor that initializes the UI with specified width and height.
         *
         * @param width The width of the UI.
         * @param height The height of the UI.
         */
        UI(std::uint16_t width, std::uint16_t height) noexcept;

        /**
         * @brief Constructor that initializes the UI with specified width, height, and title.
         *
         * @param width The width of the UI.
         * @param height The height of the UI.
         * @param title The title of the UI.
         */
        UI(std::uint16_t width, std::uint16_t height, std::string title);

    public:
        /**
         * @brief Virtual method for rendering the UI.
         *
         * This method must be implemented by derived classes to define how the UI should be rendered.
         */
        virtual void onRender() = 0;

        /**
         * @brief Virtual method for updating the UI.
         *
         * This method must be implemented by derived classes to define how the UI should be updated.
         */
        virtual void onUpdate() = 0;
   

    protected:

        /**
         * @brief The currently active menu in the application.
         */
        std::unique_ptr<menu::Menu> m_currentMenu;


        /**
         * @brief The title of the UI.
         */
        std::string m_title;

        /**
         * @brief The width of the UI.
         */
        std::uint16_t m_width{};

        /**
         * @brief The height of the UI.
         */
        std::uint16_t m_height{};
    };

} // namespace ui

#endif // UI_H
