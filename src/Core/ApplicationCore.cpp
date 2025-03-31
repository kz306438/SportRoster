#include "Core/ApplicationCore.h"

#include "Core/Utils.h"
#include "Core/Sort.h"
#include <algorithm>
#include <utility>

namespace core
{
	ApplicationCore::ApplicationCore()
		: m_storage(STORAGE_DIRECTORY) {}

	void ApplicationCore::createTeam(const std::string& team_name) {
		try {
			m_storage.createFile(team_name + ".txt");
		}
		catch (const std::runtime_error& e) {
			throw std::runtime_error("Failed to create team: " + std::string(e.what()));
		}
	}

	void ApplicationCore::deleteTeam(const std::string& team_name)
	{
		try {
			m_storage.deleteFile(team_name + ".txt");
		}
		catch (const std::invalid_argument& e) {
			throw std::invalid_argument("Failed to delete team: " + std::string(e.what()));
		}
	}

	void ApplicationCore::overwriteTeam(const std::string& team_name, const TeamDataList& teamData)
	{
		try {
			m_storage.overwriteContent(team_name + ".txt", teamData);
		}
		catch (const std::runtime_error& e) {
			throw std::runtime_error("Failed to overwrite team: " + std::string(e.what()));
		}
	}

	TeamDataList ApplicationCore::getTeam(const std::string& team_name) const {
		try {
			return m_storage.getContent(team_name + ".txt");
		}
		catch (const std::runtime_error& e) {
			throw std::runtime_error("Failed to get team: " + std::string(e.what()));
		}
	}


	std::vector<std::string> ApplicationCore::getTeams() const {
		auto files = m_storage.getFiles();
		for (auto& file : files) {
			file = utils::removeTxtExtension(file);
		}
		return files;
	}

	void ApplicationCore::addPlayer(const std::string& team, const PlayerDataList& playerData) {
		try {
			m_storage.addContent(team + ".txt", playerData);
		}
		catch (const std::runtime_error& e) {
			throw std::runtime_error("Failed to add player: " + std::string(e.what()));
		}
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

	PlayerDataList ApplicationCore::linearSearch(
		const std::string& team_name,
		const std::string& surname) const
	{
		auto result = __linearSearch(team_name, surname);

		if (!result) {
			return PlayerDataList();
		}

		return utils::playerToText(result.value());
	}

	PlayerDataList ApplicationCore::binarySearch(
		const std::string& team_name,
		const std::string& surname) const
	{
		auto result = __binarySearch(team_name, surname);

		if (!result) {
			return PlayerDataList();
		}

		return utils::playerToText(result.value());
	}

	Team ApplicationCore::__getTeam(const std::string& team_name) const
	{
		TeamDataList teamDataList = m_storage.getContent(team_name + ".txt");
		return utils::textToTeam(team_name, teamDataList);
	}

	std::optional<Player> ApplicationCore::__binarySearch(
		const std::string& team_name,
		const std::string& surname) const
	{
		Team team = __getTeam(team_name);
		const std::vector<Player>& players = team.getPlayersRef();

		int left = 0, right = players.size() - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			std::string midSurname = players[mid].getSurname();

			if ((mid > left && players[mid].getSurname() < players[mid - 1].getSurname()) ||
				(mid < right && players[mid].getSurname() > players[mid + 1].getSurname()))
			{
				return std::nullopt; 
			}

			if (midSurname == surname) {
				return players[mid];
			}
			else if (midSurname < surname) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}

		return std::nullopt;
	}


	std::optional<Player> ApplicationCore::__linearSearch(
		const std::string& team_name, 
		const std::string& surname) const
	{
		const Team team = __getTeam(team_name);
		const std::vector<Player>& players = team.getPlayersRef();

		for (const auto& player : players) {
			if (player.getSurname() == surname) {
				return player;
			}
		}
		return {};
	}

} // namespace core
