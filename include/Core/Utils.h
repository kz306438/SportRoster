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
         * @brief Adds labels to a team's data fields.
         *
         * This function takes a list of player data and adds labels (e.g., "Name: ", "Game Number: ")
         * to each field, making the data more readable.
         *
         * @param dataList The list of strings representing raw player data.
         * @return TeamDataList A list of labeled strings with field names prefixed.
         */
        [[nodiscard]] TeamDataList teamToLabeledText(const TeamDataList& dataList);

        /**
         * @brief Removes labels from a team's labeled data fields.
         *
         * This function reverses the effect of teamToLabeledText by stripping field names
         * from each entry, leaving only the raw player data.
         *
         * @param labeledDataList The list of labeled strings.
         * @return TeamDataList A list of raw player data without labels.
         */
        [[nodiscard]] TeamDataList textToTeamDataList(const TeamDataList& labeledDataList);


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
