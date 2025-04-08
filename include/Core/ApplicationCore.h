#ifndef APPLICATION_CORE_H
#define APPLICATION_CORE_H

#include <vector>
#include <optional>
#include "Player.h"
#include "Team.h"
#include "Storage.h"
#include "Utils.h"

namespace core
{
    /**
     * @brief Directory path for storing team data.
     */
    const std::string STORAGE_DIRECTORY = "storage";

    using PlayerDataList = std::vector<std::string>; ///< A list of strings representing player data.
    using TeamDataList = std::vector<std::string>; ///< A list of strings representing team data.

    /**
     * @brief The main class responsible for managing teams and players in the application.
     *
     * This class interacts with the storage to manage teams and their players, perform sorting, searching,
     * and handle various team-related operations.
     */
    class ApplicationCore
    {
    public:
        /**
         * @brief Default constructor for the ApplicationCore object.
         */
        ApplicationCore();

        /**
         * @brief Creates a new team with the specified name.
         *
         * @param team_name The name of the team to create.
         *
         * @throws std::runtime_error If the team could not be created. 
        */
        void createTeam(const std::string& team_name);

        /**
         * @brief Deletes the specified team.
         *
         * @param team_name The name of the team to delete.
         *
         * @throws std::runtime_error If the team could not be deleted.
         */
        void deleteTeam(const std::string& team_name);

        /**
         * @brief Overwrites the data of the specified team.
         *
         * @param team_name The name of the team to overwrite.
         * @param teamData The new data to replace the existing team data.
         *
         * @throws std::runtime_error If the data could not be overwritten.
         */
        void overwriteTeam(const std::string& team_name, const TeamDataList& teamData);

        /**
         * @brief Retrieves the data of a team.
         *
         * @param team_name The name of the team.
         * @return TeamDataList A list of strings representing the team's data.
         */
        [[nodiscard]] TeamDataList getTeam(const std::string& team_name) const;

        /**
         * @brief Retrieves a list of all team names.
         *
         * @return std::vector<std::string> A list of team names.
         */
        [[nodiscard]] std::vector<std::string> getTeams() const;

        /**
         * @brief Adds a player to a specified team using player data.
         *
         * @param team The name of the team.
         * @param playerData A list of strings containing the player's data.
         * @throws std::runtime_error If the player could not be added.
         */
        void addPlayer(const std::string& team, const PlayerDataList& playerData);

        /**
         *
         * @brief Finds the team with the youngest average age.
         * @return TeamDataList A list of strings representing the youngest team's data.
         * 
         * @throws std::runtime_error If storage is empty
         */
        TeamDataList findYoungestTeam() const;

        /**
         * @brief Template function for performing linear search for a player in a team based on the provided value.
         *
         * This function performs a linear search for a player in a team by the given value. The comparison is done using the provided comparator.
         * If the player is found, their text representation is returned. If not, an empty list is returned.
         *
         * @tparam T Type of the search value (e.g., surname, age).
         * @tparam Compare Type of the comparator used to compare the value with the player's field.
         *
         * @param team_name The name of the team where the player should be searched.
         * @param value The value to search for (e.g., surname or age).
         * @param comp The comparator that defines how to compare the value with the player's field.
         *
         * @return Returns the player's text representation (if found) or an empty list (if not found).
         */
        template <typename T, typename Compare>
        PlayerDataList linearSearch(
            const std::string& team_name,
            const T& value,
            Compare comp) const
        {
            auto result = __linearSearch(team_name, value, comp);

            if (!result) {
                return PlayerDataList();
            }

            return utils::playerToText(result.value());
        }


        /**
         * @brief Template function for performing binary search for a player in a team based on the provided value.
         *
         * This function performs a binary search for a player in the sorted list of players based on the given value.
         * The comparison is done using the provided comparator.
         * If the player is found, their text representation is returned. If not, an empty list is returned.
         *
         * @tparam T Type of the search value (e.g., surname, age).
         * @tparam Compare Type of the comparator used to compare the value with the player's field.
         *
         * @param team_name The name of the team where the player should be searched.
         * @param value The value to search for (e.g., surname or age).
         * @param comp The comparator that defines how to compare the value with the player's field.
         *
         * @return Returns the player's text representation (if found) or an empty list (if not found).
         */
        template <typename T, typename Compare>
        PlayerDataList binarySearch(
            const std::string& team_name,
            const T& value,
            Compare comp) const
        {
            auto result = __binarySearch(team_name, value, comp);

            if (!result) {
                return PlayerDataList();
            }

            return utils::playerToText(result.value());
        }


    private:
        /**
         * @brief Retrieves a team by name from the storage.
         *
         * @param team The name of the team to retrieve.
         * @return Team The team object containing the team data.
         */
        Team __getTeam(const std::string& team) const;

        /**
         * @brief Template function that performs a binary search for a player in a team based on the provided value and comparator.
         *
         * This function performs a binary search on the players in the specified team using the given value and comparator. If the player is found,
         * it returns the player. If not, it returns `std::nullopt`.
         *
         * @tparam T Type of the search value (e.g., surname, age).
         * @tparam Compare Type of the comparator used to compare the value with the player's field.
         *
         * @param team_name The name of the team where the search will be performed.
         * @param value The value to search for (e.g., surname or age).
         * @param comp The comparator used to compare the player's field with the search value.
         *
         * @return Returns `std::optional<Player>` containing the player if found, or `std::nullopt` if not found.
         */
        template <typename T, typename Compare>
        std::optional<Player> __binarySearch(
            const std::string& team_name,
            const T& value,
            Compare comp) const
        {
            const Team& team = __getTeam(team_name);
            const std::vector<Player>& players = team.getPlayersRef();

            auto it = utils::binary_search(players.begin(), players.end(), value, comp);

            if (it != players.end() && comp(*it, value) == false) {
                return *it;
            }
            return std::nullopt;
        }

            
        /**
         * @brief Template function that performs a linear search for a player in a team based on the provided value and comparator.
         *
         * This function performs a linear search on the players in the specified team using the given value and comparator. If the player is found,
         * it returns the player. If not, it returns `std::nullopt`.
         *
         * @tparam T Type of the search value (e.g., surname, age).
         * @tparam Compare Type of the comparator used to compare the value with the player's field.
         *
         * @param team_name The name of the team where the search will be performed.
         * @param value The value to search for (e.g., surname or age).
         * @param comp The comparator used to compare the player's field with the search value.
         *
         * @return Returns `std::optional<Player>` containing the player if found, or `std::nullopt` if not found.
         */
        template <typename T, typename Compare>
        std::optional<Player> __linearSearch(
            const std::string& team_name,
            const T& value,
            Compare comp) const
        {
            const Team& team = __getTeam(team_name);
            const std::vector<Player>& players = team.getPlayersRef();

            for (const auto& player : players) {
                if (comp(player, value)) {
                    return player;
                }
            }

            return {};
        }

    private:
        Storage m_storage; ///< Storage instance for team and player data.
    };

} // namespace core

#endif // APPLICATION_CORE_H
