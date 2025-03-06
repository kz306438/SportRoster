#ifndef UI_TYPE_H
#define UI_TYPE_H
#include <cstdint>

namespace ui
{
    /**
     * @brief Enum representing the type of user interface.
     *
     * This enum is used to specify different types of user interfaces (UI). Currently, it includes only
     * a Text-based User Interface (TUI), with a default value of Unknown.
     */
    enum class UIType : std::uint8_t
    {
        /**
         * @brief Text-based User Interface (TUI).
         *
         * Represents a terminal-based user interface, which typically uses text to display information
         * and accepts user input through the keyboard.
         */
        TUI,

        /**
         * @brief Unknown UI type.
         *
         * Used when the UI type is not recognized or specified.
         */
        Unknown
    };

} // namespace ui

#endif // UI_TYPE_H
