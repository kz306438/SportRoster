#include "Core/Utils.h"

#include <array>
#include <stdexcept>

namespace core::utils
{
    constexpr int NUMBER_OF_PLAYER_FIELDS = 7;

    PlayerDataList playerToText(const Player& player)
    {
        return {
            player.getName(),
            player.getSurname(),
            std::to_string(player.getAge()),
            std::to_string(player.getHeight()),
            std::to_string(player.getWeight()),
            std::to_string(player.getGameNumber()),
            player.getCountryName()
        };
    }

    TeamDataList teamToText(const Team& team)
    {
        TeamDataList teamDataList;
        teamDataList.reserve(team.getPlayersRef().size() * NUMBER_OF_PLAYER_FIELDS);

        for (const auto& player : team.getPlayersRef()) {
            auto playerData = playerToText(player);
            teamDataList.insert(teamDataList.end(), playerData.begin(), playerData.end());
        }

        return teamDataList;
    }

    Player textToPlayer(const PlayerDataList& dataList)
    {
        if (dataList.size() != NUMBER_OF_PLAYER_FIELDS)
            throw std::invalid_argument("Incorrect PlayerDataList object.");

        return Player(
            dataList[0],
            dataList[1],
            static_cast<std::uint16_t>(std::stoi(dataList[2])),
            static_cast<std::uint16_t>(std::stoi(dataList[3])),
            static_cast<std::uint16_t>(std::stoi(dataList[4])),
            static_cast<std::uint16_t>(std::stoi(dataList[5])),
            dataList[6]
        );
    }

    Team textToTeam(const std::string& teamname, const TeamDataList& dataList)
    {
        if (dataList.size() % NUMBER_OF_PLAYER_FIELDS != 0)
            throw std::invalid_argument("Incorrect TeamDataList object.");

        Team team(teamname);
        for (size_t i = 0; i < dataList.size(); i += NUMBER_OF_PLAYER_FIELDS) {
            team.addPlayer(textToPlayer({
                dataList[i], dataList[i + 1], dataList[i + 2],
                dataList[i + 3], dataList[i + 4], dataList[i + 5], dataList[i + 6]
                }));
        }

        return team;
    }

    TeamDataList teamToLabeledText(const TeamDataList& dataList) {
        if (dataList.size() % NUMBER_OF_PLAYER_FIELDS != 0)
            throw std::invalid_argument("Incorrect TeamDataList object.");

        TeamDataList labeledData;
        labeledData.reserve(dataList.size());

        static const std::array<std::string, NUMBER_OF_PLAYER_FIELDS> labels = {
            "Name: ", "Surname: ", "Age: ", "Height: ", "Weight: ", "Game Number: ", "Country: "
        };

        for (size_t i = 0; i < dataList.size(); i += NUMBER_OF_PLAYER_FIELDS) {
            for (size_t j = 0; j < NUMBER_OF_PLAYER_FIELDS; ++j) {
                labeledData.push_back(labels[j] + dataList[i + j]);
            }
        }

        return labeledData;
    }

    TeamDataList textToTeamDataList(const TeamDataList& labeledDataList) {
        if (labeledDataList.size() % NUMBER_OF_PLAYER_FIELDS != 0)
            throw std::invalid_argument("Incorrect TeamDataList object.");

        TeamDataList dataList;
        dataList.reserve(labeledDataList.size());

        for (const auto& labeledEntry : labeledDataList) {
            size_t colonPos = labeledEntry.find(": ");
            if (colonPos == std::string::npos || colonPos + 2 >= labeledEntry.size())
                throw std::invalid_argument("Invalid labeled entry format.");

            dataList.push_back(labeledEntry.substr(colonPos + 2));
        }

        return dataList;
    }


    double averageAgeOfTeam(const Team& team)
    {
        const auto& players = team.getPlayersRef();
        if (players.empty()) return -1.0;

        double totalAge = 0;
        for (const auto& player : players) {
            totalAge += player.getAge();
        }
        return totalAge / players.size();
    }

} // namespace core::utils
