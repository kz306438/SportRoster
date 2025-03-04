#include <gtest/gtest.h>
#include "Core/Team.h"
#include "Core/Player.h"

namespace core {

    class TeamTest : public ::testing::Test {
    protected:
        void SetUp() override {
            player1 = Player("John", "Doe", 25, 180, 75, 10, "USA");
            player2 = Player("Alice", "Smith", 23, 170, 65, 7, "UK");
            player3 = Player("Bob", "Brown", 28, 185, 80, 15, "Canada");
            player4 = Player("Charlie", "Johnson", 22, 175, 70, 9, "Australia");

            teamWithPlayers = Team("Warriors", { player1, player2 });
        }

        Player player1, player2, player3, player4;
        Team emptyTeam{ "Empty Team" };
        Team teamWithPlayers;
    };


} // namespace core
