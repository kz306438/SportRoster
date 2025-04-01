#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <colors.h>

namespace ui
{

    /**
     * @brief Represents an image consisting of characters with optional color attributes.
     */
    class Image
    {
    public:
        /**
         * @brief Constructs an image from a 2D character matrix.
         * @param inputPixels A 2D vector representing the image pixels.
         */
        Image(const std::vector<std::vector<char>>& inputPixels);

        /**
         * @brief Constructs an image from a 2D character matrix with a specified foreground color.
         * @param inputPixels A 2D vector representing the image pixels.
         * @param color The foreground color of the image.
         */
        Image(const std::vector<std::vector<char>>& inputPixels, ConsoleColor color);

    public:
        /**
         * @brief Constructs an image by loading it from a file.
         * @param filePath The path to the file containing the image data.
         */
        Image(const std::string& filePath);

        /**
         * @brief Constructs an image from a file with a specified foreground color.
         * @param filePath The path to the file containing the image data.
         * @param color The foreground color of the image.
         */
        Image(const std::string& filePath, ConsoleColor color);

    private:
        /**
         * @brief Loads image data from a 2D vector.
         * @param inputPixels The 2D vector containing image pixels.
         */
        void loadFromVector(const std::vector<std::vector<char>>& inputPixels);

        /**
         * @brief Loads image data from a file.
         * @param filePath The path to the file containing image data.
         */
        void loadFromFile(const std::string& filePath);

    public:
        /**
         * @brief Renders the image at its current position.
         */
        void render() const;

        /**
         * @brief Renders the image at a specified position.
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         */
        void render(int x, int y) const;

    public:
        /**
         * @brief Sets the value of a pixel at a specified position.
         * @param x The x-coordinate of the pixel.
         * @param y The y-coordinate of the pixel.
         * @param value The new character value for the pixel.
         */
        void setPixel(int x, int y, char value);

        /**
         * @brief Gets the character value of a pixel at a specified position.
         * @param x The x-coordinate of the pixel.
         * @param y The y-coordinate of the pixel.
         * @return The character value of the pixel.
         */
        char getPixel(int x, int y) const;

        /**
         * @brief Fills the entire image with a specified character.
         * @param fill_char The character to fill the image with.
         */
        void fill(char fill_char);

    public:
        /**
         * @brief Gets the width of the image.
         * @return The width of the image.
         */
        int getWidth() const;

        /**
         * @brief Gets the height of the image.
         * @return The height of the image.
         */
        int getHeight() const;

        /**
         * @brief Retrieves the pixel matrix of the image.
         * @return A 2D vector representing the image.
         */
        [[nodiscard]] std::vector<std::vector<char>> getMatrix();

    public:
        /**
         * @brief Sets the foreground color of the image.
         * @param clr The foreground color.
         */
        void setFgColor(const ConsoleColor& clr);

        /**
         * @brief Sets the background color of the image.
         * @param clr The background color.
         */
        void setBgColor(const ConsoleColor& clr);

        /**
         * @brief Sets the position of the image.
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         */
        void setPosition(int x, int y);

    private:
        std::vector<std::vector<char>> m_pixels; ///< Stores the image pixel data.

    private:
        int m_width; ///< The width of the image.
        int m_height; ///< The height of the image.

        int m_posX = 0; ///< The x-coordinate of the image position.
        int m_posY = 0; ///< The y-coordinate of the image position.

        ConsoleColor fgColor = White; ///< Foreground color.
        ConsoleColor bgColor = Black; ///< Background color.
    };

} // namespace ui

#endif // IMAGE_H
