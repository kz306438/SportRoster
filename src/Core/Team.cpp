#include "Core/Team.h"

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
        m_cachedPlayers.reset();
    }

    void Team::removePlayer(std::uint16_t gameNumber) {
        m_players.erase(gameNumber);
        m_cachedPlayers.reset();
    }

    std::string Team::getTeamName() const {
        return m_teamName;
    }

    std::vector<Player> Team::getPlayers() const {
        return convertToVector();
    }

    const std::vector<Player>& Team::getPlayersRef() const {
        if (!m_cachedPlayers.has_value()) {
            m_cachedPlayers = convertToVector();
        }
        return m_cachedPlayers.value();
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