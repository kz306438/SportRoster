#ifndef IAPPLICATION_CORE_H
#define IAPPLICATION_CORE_H

#include <string>
#include <vector>
#include <optional>

#include "Player.h"
#include "Team.h"

namespace core
{

	class IApplicationCore
	{
	public:
        virtual ~IApplicationCore() = default;

        virtual void createFile(const std::string& filename) = 0;
       
        virtual void viewFile(const std::string& filename) = 0;

        virtual void addEntry(const std::string& filename, const Player& entry) = 0;

        virtual Team linearSearch(const std::string& filename, std::uint16_t gameNumber) = 0;

        virtual void selectionSort(const std::string& filename) = 0;

        virtual void quickSort(const std::string& filename) = 0;

        virtual std::optional<Player> binarySearch(const std::string& filename, int key) = 0;

        virtual Team findYoungestTeam(const std::vector<std::string>& filenames) = 0;
	};

} // namespace core

#endif // IAPPLICATION_CORE_H