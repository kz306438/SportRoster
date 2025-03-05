#include "Core/ApplicationCore.h"

#include "Core/Utils.h"
#include <algorithm>

namespace core
{
	ApplicationCore::ApplicationCore()
		: m_storage(STORAGE_DIRECTORY) {}

	void ApplicationCore::createTeam(const std::string& team_name) {
		m_storage.createFile(team_name);
	}

	TeamDataList ApplicationCore::getTeam(const std::string& team_name) const {
		return m_storage.getContent(team_name);
	}

	void ApplicationCore::addPlayer(const std::string& team, const PlayerDataList& playerData) {
		m_storage.addContent(team, playerData);
	}

	TeamDataList ApplicationCore::findYoungestTeam() const
	{
		std::vector<std::string> files = m_storage.getFiles();
		if (files.empty())
			throw std::runtime_error("Storage is empty!");

		Team youngestTeam;
		double minAverageAgeOfTeam = std::numeric_limits<double>::max();

		for (const auto& file : files)
		{
			Team team = __getTeam(file);
			double averageAgeOfTeam = utils::averageAgeOfTeam(team);
			if (averageAgeOfTeam < minAverageAgeOfTeam) {
				minAverageAgeOfTeam = averageAgeOfTeam;
				youngestTeam = team;
			}
		}

		return utils::teamToText(youngestTeam);
	}

	PlayerDataList ApplicationCore::linearSearch(const std::string& team_name, std::uint16_t game_number) const
	{
		auto result = __linearSearch(team_name, game_number);

		if (!result) {
			throw std::runtime_error("Player not found!");
		}

		return utils::playerToText(result.value());
	}

	PlayerDataList ApplicationCore::binarySearch(const std::string& team_name, std::uint16_t gameNumber) const
	{
		auto result = __binarySearch(team_name, gameNumber);

		if (!result) {
			throw std::runtime_error("Player not found!");
		}

		return utils::playerToText(result.value());
	}

	Team ApplicationCore::__getTeam(const std::string& team_name) const
	{
		TeamDataList teamDataList = m_storage.getContent(team_name);
		return utils::textToTeam(team_name, teamDataList);
	}

	std::optional<Player> ApplicationCore::__binarySearch(const std::string& team_name, std::uint16_t game_number) const
	{
		Team team = __getTeam(team_name);
		const std::vector<Player>& players = team.getPlayersRef();

		if (!std::is_sorted(players.begin(), players.end(),
			[](const Player& p1, const Player& p2) {
				return p1.getGameNumber() < p2.getGameNumber();
			}))
		{
			return std::nullopt;
		}

		int left = 0, right = players.size() - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			std::uint16_t midGameNumber = players[mid].getGameNumber();

			if (midGameNumber == game_number) {
				return players[mid];
			}
			else if (midGameNumber < game_number) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}

		return std::nullopt;
	}

	std::optional<Player> ApplicationCore::__linearSearch(const std::string& team_name, std::uint16_t game_number) const
	{
		const Team team = __getTeam(team_name);
		const std::vector<Player>& players = team.getPlayersRef();

		for (const auto& player : players) {
			if (player.getGameNumber() == game_number) {
				return player;
			}
		}
		return {};
	}

} // namespace core
