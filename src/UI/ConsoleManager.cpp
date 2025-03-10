#include "UI/ConsoleManager.h"
#include <iostream>

namespace ui
{

	ConsoleManager& ConsoleManager::getInstance()
	{
		static ConsoleManager instance;
		return instance;
	}

	ConsoleManager::ConsoleManager()
	{
		m_consoleWindow = GetConsoleWindow();
		m_consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		if (m_consoleWindow == NULL || m_consoleOutput == INVALID_HANDLE_VALUE)
		{
			std::cerr << "Error receiving handle." << std::endl;
		}
	}

	ConsoleManager::~ConsoleManager() { }

	void ConsoleManager::disableResize()
	{
		if (m_consoleWindow)
		{
			LONG_PTR style = GetWindowLongPtr(m_consoleWindow, GWL_STYLE);
			style &= ~WS_SIZEBOX;
			SetWindowLongPtr(m_consoleWindow, GWL_STYLE, style);
			SetWindowPos(m_consoleWindow, NULL, 0, 0, 0, 0,
				SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		}
	}

	void ConsoleManager::setTitle(const std::string& title)
	{
		SetConsoleTitleA(title.c_str());
	}

	void ConsoleManager::setSize(int width, int height)
	{
		SMALL_RECT rect;
		COORD coord;

		coord.X = width;
		coord.Y = height;

		rect.Top = 0;
		rect.Left = 0;
		rect.Bottom = height - 1;
		rect.Right = width - 1;

		SetConsoleScreenBufferSize(m_consoleOutput, coord);
		SetConsoleWindowInfo(m_consoleOutput, TRUE, &rect);
	}

	int ConsoleManager::getWidth()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(m_consoleOutput, &csbi))
		{
			return csbi.srWindow.Right - csbi.srWindow.Left + 1;
		}
		return 0;
	}

	int ConsoleManager::getHeight()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(m_consoleOutput, &csbi))
		{
			return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		}
		return 0;
	}

	void ConsoleManager::disableScrollbars()
	{
		if (m_consoleOutput != INVALID_HANDLE_VALUE)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			if (GetConsoleScreenBufferInfo(m_consoleOutput, &csbi))
			{
				COORD newSize;
				newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
				newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

				SetConsoleScreenBufferSize(m_consoleOutput, newSize);
			}
		}
	}

	void ConsoleManager::setCursorPosition(int x, int y)
	{
		if (m_consoleOutput != INVALID_HANDLE_VALUE)
		{
			COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
			SetConsoleCursorPosition(m_consoleOutput, position);
		}
	}

	void ConsoleManager::setCursorVisibility(bool visible)
	{
		if (m_consoleOutput != INVALID_HANDLE_VALUE)
		{
			CONSOLE_CURSOR_INFO cursorInfo;
			GetConsoleCursorInfo(m_consoleOutput, &cursorInfo);
			cursorInfo.bVisible = visible;
			SetConsoleCursorInfo(m_consoleOutput, &cursorInfo);
		}
	}

	void ConsoleManager::setFontSize(int width, int height)
	{
		if (m_consoleOutput != INVALID_HANDLE_VALUE)
		{
			CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };
			GetCurrentConsoleFontEx(m_consoleOutput, FALSE, &cfi);
			cfi.dwFontSize.X = width;
			cfi.dwFontSize.Y = height;
			SetCurrentConsoleFontEx(m_consoleOutput, FALSE, &cfi);
		}
	}

	void ConsoleManager::clearScreen() {
		if (m_consoleOutput != INVALID_HANDLE_VALUE) {
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			DWORD count;
			DWORD cellCount;
			COORD homeCoords = { 0, 0 };

			if (GetConsoleScreenBufferInfo(m_consoleOutput, &csbi)) {
				cellCount = csbi.dwSize.X * csbi.dwSize.Y;
				FillConsoleOutputCharacter(m_consoleOutput, ' ', cellCount, homeCoords, &count);
				FillConsoleOutputAttribute(m_consoleOutput, csbi.wAttributes, cellCount, homeCoords, &count);
				SetConsoleCursorPosition(m_consoleOutput, homeCoords);
			}
		}
	}

	void ConsoleManager::setColorBackground(ConsoleColor color) {
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(m_consoleOutput, &consoleInfo);
		WORD attributes = consoleInfo.wAttributes;
		attributes &= 0x0F;
		attributes |= ((WORD)color << 4);
		SetConsoleTextAttribute(m_consoleOutput, attributes);
	}

	void ConsoleManager::setColorForeground(ConsoleColor color) {
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(m_consoleOutput, &consoleInfo);
		WORD attributes = consoleInfo.wAttributes;
		attributes &= 0xF0;
		attributes |= (WORD)color;
		SetConsoleTextAttribute(m_consoleOutput, attributes);
	}

	void ConsoleManager::saveConsoleAttributes() {
		GetConsoleScreenBufferInfo(m_consoleOutput, &m_savedConsoleInfo);
		m_savedAttributes = m_savedConsoleInfo.wAttributes;
	}

	void ConsoleManager::restoreConsoleAttributes() {
		SetConsoleTextAttribute(m_consoleOutput, m_savedAttributes);
	}

} // namespace ui