#include "Team.h"

#include <algorithm>

namespace core
{

	Team::Team(const std::string& teamName)
		: m_teamName(teamName) {}

    Team::Team(const std::string& teamName, const std::vector<Player>& players)
        : m_teamName(teamName) { 
        convertToMap(players);
    }

    void Team::addPlayer(const Player& newPlayer) {
        m_players[newPlayer.getGameNumber()] = newPlayer;
    }

    void Team::removePlayer(std::uint16_t gameNumber) {
        m_players.erase(gameNumber);
    }

    [[nodiscard]] std::string Team::getTeamName() const {
        return m_teamName;
    }

    [[nodiscard]] std::vector<Player> Team::getPlayers() const {
        return convertToVector();
    }

    [[nodiscard]] Player Team::getPlayer(std::uint16_t gameNumber) {
        return m_players[gameNumber];
    }

    void Team::convertToMap(const std::vector<Player>& vec) {
        for (const auto& player : vec) {
            m_players[player.getGameNumber()] = player;
        }
    }

    std::vector<Player> Team::convertToVector() const {
        std::vector<Player> players;
        players.reserve(m_players.size());
        for (const auto& [gameNumber, player] : m_players) {
            players.push_back(player);
        }
        return players;
    }

} // namespace core