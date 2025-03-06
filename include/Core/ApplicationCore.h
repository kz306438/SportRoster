#ifndef APPLICATION_CORE_H
#define APPLICATION_CORE_H

#include <vector>
#include <optional>
#include "Player.h"
#include "Team.h"
#include "Storage.h"

namespace core
{
    const std::string STORAGE_DIRECTORY = "storage";

    using PlayerDataList = std::vector<std::string>;
    using TeamDataList   = std::vector<std::string>;

	class ApplicationCore
	{
	public:
        ApplicationCore();

        void createTeam(const std::string& team_name);
        [[nodiscard]] TeamDataList getTeam(const std::string& team_name) const;

        void addPlayer(const std::string& team, const PlayerDataList& playerData);

        void selectionSort(const std::string& team_name);
        void quickSort(const std::string& team_name);
        
        TeamDataList findYoungestTeam() const;

        [[nodiscard]] PlayerDataList linearSearch(const std::string& team_name, std::uint16_t gameNumber) const;
        [[nodiscard]] PlayerDataList binarySearch(const std::string& team_name, std::uint16_t gameNumber) const;

    private:
        Team __getTeam(const std::string& team) const;
        
        std::optional<Player> __binarySearch(const std::string& team_name, std::uint16_t game_number) const;
        std::optional<Player> __linearSearch(const std::string& team_name, std::uint16_t game_number) const;
	
    private:
        Storage m_storage;
    };

} // namespace core

#endif // APPLICATION_CORE_H2
