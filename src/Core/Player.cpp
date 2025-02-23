#include "Player.h"

namespace core
{

    Player::Player(const std::string& name,
        const std::string& surname,
        std::uint16_t age,
        std::uint16_t height,
        std::uint16_t weight,
        std::uint16_t gameNumber,
        const std::string& countryName)
        : m_name(name),
        m_surname(surname),
        m_age(age),
        m_height(height),
        m_weight(weight),
        m_gameNumber(gameNumber),
        m_countryName(countryName)
    {
    }

    std::string Player::getName() const noexcept {
        return m_name; 
    }

    std::string Player::getSurname() const noexcept {
        return m_surname;
    }

    std::uint16_t Player::getAge() const noexcept {
        return m_age;
    }

    std::uint16_t Player::getHeight() const noexcept {
        return m_height;
    }

    std::uint16_t Player::getWeight() const noexcept {
        return m_weight;
    }

    std::uint16_t Player::getGameNumber() const noexcept {
        return m_gameNumber;
    }

    std::string Player::getCountryName() const noexcept {
        return m_countryName;
    }

} // namespace core