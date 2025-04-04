#include "Core/Team.h"

#include <algorithm>

namespace core
{

    Team::Team(const std::string& teamName)
        : m_teamName(teamName) {}

    Team::Team(const std::string& teamName, const std::vector<Player>& players)
        : m_teamName(teamName), m_players(players) {}

    void Team::addPlayer(const Player& newPlayer) {
        m_players.push_back(newPlayer);
    }

    void Team::addAllPlayers(const std::vector<Player>& players) {
        m_players = players;
    }

    void Team::removeAllPlayers() {
        m_players.clear();
    }

    std::string Team::getTeamName() const {
        return m_teamName;
    }

    std::vector<Player> Team::getPlayers() const {
        return m_players;
    }

    const std::vector<Player>& Team::getPlayersRef() const {
        return m_players;
    }

} // namespace core
