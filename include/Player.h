#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace core
{
	class Player final
	{
	public:
		Player() = default;
		Player(const std::string& name,
			const std::string& surname,
			std::uint16_t age,
			std::uint16_t height,
			std::uint16_t weight,
			std::uint16_t gameNumber,
			const std::string& countryName);

		std::string		 getName()			 const noexcept;
		std::string		 getSurname()		 const noexcept;

		std::uint16_t	 getAge()			 const noexcept;
		std::uint16_t	 getHeight()		 const noexcept;
		std::uint16_t	 getWeight()		 const noexcept;

		std::uint16_t	 getGameNumber()	 const noexcept;
		std::string		 getCountryName()	 const noexcept;

	private:
		std::string m_name;
		std::string m_surname;

		std::uint16_t m_age{};
		std::uint16_t m_height{};
		std::uint16_t m_weight{};

		std::uint16_t m_gameNumber{};
		std::string m_countryName;
	};

} // namespace core

#endif // PLAYER_H