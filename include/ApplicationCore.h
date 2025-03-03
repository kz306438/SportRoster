#ifndef APPLICATION_CORE_H
#define APPLICATION_CORE_H

#include <vector>
#include <optional>
#include "Player.h"
#include "Team.h"


namespace core
{

	class ApplicationCore
	{
	public:
        void createFile(const std::string& filename);

        void viewFile(const std::string& filename);

        void addEntry(const std::string& filename, const Player& entry);

        Team linearSearch(const std::string& filename, std::uint16_t gameNumber);

        void selectionSort(const std::string& filename);

        void quickSort(const std::string& filename);

        std::optional<Player> binarySearch(const std::string& filename, int key);

        Team findYoungestTeam(const std::vector<std::string>& filenames);
	};

} // namespace core

#endif // APPLICATION_CORE_H
