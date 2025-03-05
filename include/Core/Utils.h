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

		[[nodiscard]] PlayerDataList playerToText(const Player& player);

		[[nodiscard]] TeamDataList teamToText(const Team& team);

		[[nodiscard]] Player textToPlayer(const PlayerDataList& dataList);
		
		[[nodiscard]] Team textToTeam(const std::string& teamname, const TeamDataList& dataList);

		[[nodiscard]] double averageAgeOfTeam(const Team& team);

	} // namespace utils

} // namespace core

#endif // UTILS_H
