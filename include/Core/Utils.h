#ifndef UTILS_H
#define UTILS_H

#include <optional>
#include "Player.h"
#include "Team.h"
#include "ApplicationCore.h"

namespace core
{

    namespace utils
    {
        /**
         * @brief Converts a Player object to a text representation.
         *
         * This function serializes a Player object to a list of strings.
         *
         * @param player The Player object to convert.
         * @return PlayerDataList A list of strings representing the player's data.
         */
        [[nodiscard]] PlayerDataList playerToText(const Player& player);

        /**
         * @brief Converts a Team object to a text representation.
         *
         * This function serializes a Team object to a list of strings representing all players in the team.
         *
         * @param team The Team object to convert.
         * @return TeamDataList A list of strings representing the team's data.
         */
        [[nodiscard]] TeamDataList teamToText(const Team& team);

        /**
         * @brief Converts a list of text data into a Player object.
         *
         * This function deserializes a list of strings into a Player object.
         *
         * @param dataList The list of strings representing player data.
         * @return Player The Player object created from the given data.
         */
        [[nodiscard]] Player textToPlayer(const PlayerDataList& dataList);

        /**
         * @brief Converts a list of text data into a Team object.
         *
         * This function deserializes a list of strings into a Team object.
         *
         * @param teamname The name of the team.
         * @param dataList The list of strings representing the team's data.
         * @return Team The Team object created from the given data.
         */
        [[nodiscard]] Team textToTeam(const std::string& teamname, const TeamDataList& dataList);

        /**
         * @brief Calculates the average age of all players in a team.
         *
         * This function computes the average age of the players in the given team.
         *
         * @param team The team whose players' ages will be averaged.
         * @return double The average age of the players in the team.
         */
        [[nodiscard]] double averageAgeOfTeam(const Team& team);

    } // namespace utils

} // namespace core

#endif // UTILS_H
