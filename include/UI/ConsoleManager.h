#pragma once
#include <windows.h>
#include <string>

namespace ui
{

    class ConsoleManager
    {
    public:
        static ConsoleManager& getInstance();

        ConsoleManager(const ConsoleManager&) = delete;
        ConsoleManager& operator=(const ConsoleManager&) = delete;

    public:
        void DisableResize();
        void DisableScrollbars();

        int GetWidth();
        int GetHeight();

        void SetTitle(const std::string& title);
        void SetSize(int width, int height);
        void SetCursorPosition(int x, int y);
        void SetCursorVisibility(bool visible);
        void SetFontSize(int width, int height);

        void ClearScreen();

    private:
        ConsoleManager();
        ~ConsoleManager();

    private:
        HWND m_consoleWindow;
        HANDLE m_consoleOutput;
    };

} // namespace ui
