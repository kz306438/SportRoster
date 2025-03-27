#ifndef APPLICATION_CORE_H
#define APPLICATION_CORE_H

#include <vector>
#include <optional>
#include "Player.h"
#include "Team.h"
#include "Storage.h"

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
         * @brief Sorts the players in a team using selection sort.
         *
         * @param team_name The name of the team to sort.
         */
        void selectionSort(const std::string& team_name);

        /**
         * @brief Sorts the players in a team using quicksort.
         *
         * @param team_name The name of the team to sort.
         */
        void quickSort(const std::string& team_name);

        /**
         * @brief Finds the team with the youngest average age.
         *
         * @return TeamDataList A list of strings representing the youngest team's data.
         * 
         * @throws std::runtime_error If storage is empty
         */
        TeamDataList findYoungestTeam() const;

        /**
         * @brief Performs a linear search to find a player by game number in a team.
         *
         * @param team_name The name of the team.
         * @param gameNumber The game number of the player to find.
         * @return PlayerDataList A list of strings representing the player's data if found.
         * 
         * @throws throw std::runtime_error If the player was not found
         */
        [[nodiscard]] PlayerDataList linearSearch(const std::string& team_name, std::uint16_t gameNumber) const;

        /**
         * @brief Performs a binary search to find a player by game number in a team.
         *
         * @param team_name The name of the team.
         * @param gameNumber The game number of the player to find.
         * @return PlayerDataList A list of strings representing the player's data if found.
         * 
         * @throws throw std::runtime_error If the player was not found
         */
        [[nodiscard]] PlayerDataList binarySearch(const std::string& team_name, std::uint16_t gameNumber) const;

    private:
        /**
         * @brief Retrieves a team by name from the storage.
         *
         * @param team The name of the team to retrieve.
         * @return Team The team object containing the team data.
         */
        Team __getTeam(const std::string& team) const;

        /**
         * @brief Performs a binary search to find a player by their game number in a team.
         *
         * @param team_name The name of the team.
         * @param game_number The game number of the player.
         * @return std::optional<Player> The player if found, otherwise an empty optional.
         */
        std::optional<Player> __binarySearch(const std::string& team_name, std::uint16_t game_number) const;
            
        /**
         * @brief Performs a linear search to find a player by their game number in a team.
         *
         * @param team_name The name of the team.
         * @param game_number The game number of the player.
         * @return std::optional<Player> The player if found, otherwise an empty optional.
         */
        std::optional<Player> __linearSearch(const std::string& team_name, std::uint16_t game_number) const;

    private:
        Storage m_storage; ///< Storage instance for team and player data.
    };

} // namespace core

#endif // APPLICATION_CORE_H
