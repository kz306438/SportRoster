#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace core
{
    /**
     * @brief A class representing a player with personal details and game statistics.
     *
     * This class holds information such as the player's name, surname, age, height, weight,
     * game number, and country of origin.
     */
    class Player final
    {
    public:
        /**
         * @brief Default constructor for a Player object.
         */
        Player() = default;

        /**
         * @brief Constructs a Player object with the specified details.
         *
         * @param name The player's first name.
         * @param surname The player's last name.
         * @param age The player's age.
         * @param height The player's height in centimeters.
         * @param weight The player's weight in kilograms.
         * @param gameNumber The player's game number.
         * @param countryName The country the player is from.
         */
        Player(const std::string& name,
            const std::string& surname,
            std::uint16_t age,
            std::uint16_t height,
            std::uint16_t weight,
            std::uint16_t gameNumber,
            const std::string& countryName);

        /**
         * @brief Retrieves the player's first name.
         *
         * @return std::string The player's first name.
         */
        std::string getName() const noexcept;

        /**
         * @brief Retrieves the player's last name.
         *
         * @return std::string The player's last name.
         */
        std::string getSurname() const noexcept;

        /**
         * @brief Retrieves the player's age.
         *
         * @return std::uint16_t The player's age.
         */
        std::uint16_t getAge() const noexcept;

        /**
         * @brief Retrieves the player's height.
         *
         * @return std::uint16_t The player's height in centimeters.
         */
        std::uint16_t getHeight() const noexcept;

        /**
         * @brief Retrieves the player's weight.
         *
         * @return std::uint16_t The player's weight in kilograms.
         */
        std::uint16_t getWeight() const noexcept;

        /**
         * @brief Retrieves the player's game number.
         *
         * @return std::uint16_t The player's game number.
         */
        std::uint16_t getGameNumber() const noexcept;

        /**
         * @brief Retrieves the country the player is from.
         *
         * @return std::string The country of the player.
         */
        std::string getCountryName() const noexcept;

    private:
        std::string m_name;       ///< The player's first name
        std::string m_surname;    ///< The player's last name

        std::uint16_t m_age{};    ///< The player's age
        std::uint16_t m_height{}; ///< The player's height in centimeters
        std::uint16_t m_weight{}; ///< The player's weight in kilograms

        std::uint16_t m_gameNumber{}; ///< The player's game number
        std::string m_countryName;    ///< The country the player is from
    };

} // namespace core

#endif // PLAYER_H
