#include "UI/Image.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include "UI/ConsoleManager.h"

namespace ui
{

    Image::Image(const std::vector<std::vector<char>>& inputPixels) {
        loadFromVector(inputPixels);
    }

    Image::Image(const std::vector<std::vector<char>>& inputPixels, ConsoleColor color)
        : Image(inputPixels)
    {
        fgColor = color;
    }

    Image::Image(const std::string& filePath) {
        loadFromFile(filePath);
    }

    Image::Image(const std::string& filePath, ConsoleColor color) : Image(filePath)
    {
        fgColor = color;
    }

    void Image::loadFromVector(const std::vector<std::vector<char>>& inputPixels) {
        m_pixels = inputPixels;
        m_height = m_pixels.size();
        m_width = 0;
        for (const auto& row : m_pixels) {
            if (row.size() > m_width) {
                m_width = row.size();
            }
        }
    }

    void Image::loadFromFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file) {
            throw std::runtime_error("Could not open file");
        }

        m_pixels.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<char> row;
            int value;
            while (iss >> value) {
                row.push_back(static_cast<char>(value));
            }
            m_pixels.push_back(row);
        }

        m_height = m_pixels.size();
        m_width = 0;
        for (const auto& row : m_pixels) {
            if (row.size() > m_width) {
                m_width = row.size();
            }
        }

        file.close();
    }
    void Image::setPixel(int x, int y, char value) {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            if (x >= m_pixels[y].size()) {
                m_pixels[y].resize(x + 1, ' ');
            }
            m_pixels[y][x] = value;
        }
    }

    char Image::getPixel(int x, int y) const {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            if (x < m_pixels[y].size()) {
                return m_pixels[y][x];
            }
        }
        return ' ';
    }

    std::vector<std::vector<char>> Image::getMatrix()
    {
        return m_pixels;
    }


    void Image::render() const {
        saveConsoleAttributes();
        setColorForeground(fgColor);
        setColorBackground(bgColor);
        for (int i = 0; i < m_pixels.size(); ++i)
        {
            for (int j = 0; j < m_pixels[i].size(); ++j)
            {
                ConsoleManager::getInstance().setCursorPosition(m_posX + j, m_posY + i);
                std::cout << m_pixels[i][j];
            }
        }
        restoreConsoleAttributes();
    }

    void Image::render(int x, int y) const {
        saveConsoleAttributes();
        setColorForeground(fgColor);
        setColorBackground(bgColor);
        for (int i = 0; i < m_pixels.size(); ++i)
        {
            for (int j = 0; j < m_pixels[i].size(); ++j)
            {
                ConsoleManager::getInstance().setCursorPosition(x + j, y + i);
                std::cout << m_pixels[i][j];
            }
        }
        restoreConsoleAttributes();
    }

    void Image::fill(char fill_char) {
        for (auto& row : m_pixels) {
            std::fill(row.begin(), row.end(), fill_char);
            row.resize(m_width, fill_char);
        }
    }

    int Image::getWidth() const {
        return m_width;
    }

    int Image::getHeight() const {
        return m_height;
    }
    void Image::setFgColor(const ConsoleColor& clr)
    {
        fgColor = clr;
    }
    void Image::setBgColor(const ConsoleColor& clr)
    {
        bgColor = clr;
    }
    void Image::setPosition(int x, int y)
    {
        m_posX = x;
        m_posY = y;
    }

} // namespace ui