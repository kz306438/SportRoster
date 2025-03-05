#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include "Player.h"

namespace core
{

	class Team final
	{
	public:
		Team() = default;
		Team(const std::string& teamName);
		Team(const std::string& teamName, const std::vector<Player>& players);

		void addPlayer(const Player& newPlayer);
		void removePlayer(std::uint16_t gameNumber);

		std::string getTeamName() const;

		[[nodiscard]] std::vector<Player> getPlayers() const;
		[[nodiscard]] const std::vector<Player>& getPlayersRef() const;
		[[nodiscard]] Player getPlayer(std::uint16_t gameNumber);

	private:
		void convertToMap(const std::vector<Player>& vec);
		std::vector<Player> convertToVector() const;

	private:
		std::string m_teamName;
		std::unordered_map<int, Player> m_players;

	private:
		mutable std::optional<std::vector<Player>> m_cachedPlayers;
	};

} // namespace core

#endif // TEAM_H