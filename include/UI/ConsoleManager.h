#pragma once
#include <windows.h>
#include <string>

namespace ui
{
    /**
     * @brief Singleton class for managing console window settings and attributes.
     *
     * The ConsoleManager class is responsible for configuring and managing various aspects of the console window
     * such as resizing, scrollbars, cursor visibility, font size, and window title. It also provides methods for
     * controlling the console's appearance and behavior.
     */
    class ConsoleManager
    {
    public:
        /**
         * @brief Gets the singleton instance of the ConsoleManager.
         *
         * @return A reference to the ConsoleManager instance.
         */
        static ConsoleManager& getInstance();

        // Delete the copy constructor and assignment operator to prevent copying.
        ConsoleManager(const ConsoleManager&) = delete;
        ConsoleManager& operator=(const ConsoleManager&) = delete;

    public:
        /**
         * @brief Disables the ability to resize the console window.
         *
         * This method fixes the size of the console window, preventing the user from resizing it.
         */
        void DisableResize();

        /**
         * @brief Disables the console's scrollbars.
         *
         * This method hides or disables the scrollbars in the console window.
         */
        void DisableScrollbars();

        /**
         * @brief Retrieves the current width of the console window.
         *
         * @return The width of the console window in characters.
         */
        int GetWidth();

        /**
         * @brief Retrieves the current height of the console window.
         *
         * @return The height of the console window in characters.
         */
        int GetHeight();

        /**
         * @brief Sets the title of the console window.
         *
         * @param title The new title to set for the console window.
         */
        void SetTitle(const std::string& title);

        /**
         * @brief Sets the size of the console window.
         *
         * @param width The desired width of the console window in characters.
         * @param height The desired height of the console window in characters.
         */
        void SetSize(int width, int height);

        /**
         * @brief Sets the position of the cursor in the console window.
         *
         * @param x The x-coordinate (column) to move the cursor to.
         * @param y The y-coordinate (row) to move the cursor to.
         */
        void SetCursorPosition(int x, int y);

        /**
         * @brief Controls the visibility of the cursor.
         *
         * @param visible If true, the cursor will be visible; if false, it will be hidden.
         */
        void SetCursorVisibility(bool visible);

        /**
         * @brief Sets the font size of the console text.
         *
         * @param width The width (size) of the font.
         * @param height The height (size) of the font.
         */
        void SetFontSize(int width, int height);

        /**
         * @brief Clears the console screen.
         *
         * This method clears all text and resets the console screen.
         */
        void ClearScreen();

    private:
        // Private constructor to ensure the class is used as a singleton.
        ConsoleManager();

        // Private destructor.
        ~ConsoleManager();

    private:
        /**
         * @brief Handle to the console window.
         */
        HWND m_consoleWindow;

        /**
         * @brief Handle to the console's output buffer.
         */
        HANDLE m_consoleOutput;
    };

} // namespace ui
