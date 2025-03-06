#ifndef TUI_H
#define TUI_H

#include "UI.h"
#include "Menu/MenuType.h"
#include "Core/ApplicationCore.h"

namespace ui
{
    /**
     * @brief Class representing a Text-based User Interface (TUI) that inherits from the UI class.
     *
     * This class provides specific functionality for rendering and updating a text-based user interface
     * and allows interaction with the application core. It also handles setting the menu type and initializing
     * the interface based on the application core.
     */
    class TUI final : public UI
    {
    public:
        /**
         * @brief Constructor that initializes the TUI with specified width, height, and application core reference.
         *
         * @param width The width of the TUI.
         * @param height The height of the TUI.
         * @param appCore A reference to the core application that drives the logic.
         */
        TUI(std::uint16_t width, std::uint16_t height, core::ApplicationCore& appCore) noexcept;

        /**
         * @brief Constructor that initializes the TUI with specified width, height, title, and application core reference.
         *
         * @param width The width of the TUI.
         * @param height The height of the TUI.
         * @param title The title of the TUI.
         * @param appCore A reference to the core application that drives the logic.
         */
        TUI(std::uint16_t width, std::uint16_t height, std::string title, core::ApplicationCore& appCore);

    public:
        /**
         * @brief Renders the TUI on the screen.
         *
         * This method must be implemented to define how the TUI is displayed. It is called to update
         * the user interface during each cycle.
         */
        void onRender() override;

        /**
         * @brief Updates the TUI.
         *
         * This method must be implemented to define the behavior and logic for updating the TUI.
         * It is responsible for handling user input or other updates.
         */
        void onUpdate() override;

        /**
         * @brief Sets the menu type for the TUI.
         *
         * Allows switching between different types of menus within the TUI.
         *
         * @param type The menu type to be set.
         */
        void setMenu(menu::MenuType type);

    private:
        /**
         * @brief Initializes the TUI.
         *
         * This private method is used for initial setup and configuration when the TUI is created.
         */
        void init();

    private:
        /**
         * @brief A reference to the core application, used for accessing business logic.
         */
        core::ApplicationCore& m_appCore;
    };

} // namespace ui

#endif // TUI_H
