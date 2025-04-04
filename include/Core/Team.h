#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <unordered_map>
#include <optional>
#include <vector>
#include "Player.h"

namespace core
{
    /**
     * @brief A class representing a team with players.
     *
     * The class manages a collection of players, allowing operations to add, remove, and retrieve players,
     * as well as storing the team's name.
     */
    class Team final
    {
    public:
        /**
         * @brief Default constructor for a Team object.
         */
        Team() = default;

        /**
         * @brief Constructs a Team object with the specified team name.
         *
         * @param teamName The name of the team.
         */
        Team(const std::string& teamName);

        /**
         * @brief Constructs a Team object with the specified team name and a list of players.
         *
         * @param teamName The name of the team.
         * @param players A vector of Player objects to be added to the team.
         */
        Team(const std::string& teamName, const std::vector<Player>& players);

        /**
         * @brief Adds a new player to the team.
         *
         * @param newPlayer The player to be added to the team.
         */
        void addPlayer(const Player& newPlayer);

        /**
         * @brief Adds multiple players to the team.
         *
         * @param players A vector of Player objects to be added to the team.
         */
        void addAllPlayers(const std::vector<Player>& players);

        /**
         * @brief Removes all players from the team.
         */
        void removeAllPlayers();

        /**
         * @brief Retrieves the name of the team.
         *
         * @return std::string The name of the team.
         */
        std::string getTeamName() const;

        /**
         * @brief Retrieves a list of all players in the team.
         *
         * @return std::vector<Player> A vector containing all Player objects in the team.
         */
        [[nodiscard]] std::vector<Player> getPlayers() const;

        /**
         * @brief Retrieves a reference to the list of all players in the team.
         *
         * @return const std::vector<Player>& A constant reference to the vector of players.
         */
        [[nodiscard]] const std::vector<Player>& getPlayersRef() const;

    private:
        std::string m_teamName; 
        std::vector<Player> m_players;
    };

} // namespace core

#endif // TEAM_H
