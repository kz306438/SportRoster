#include <gtest/gtest.h>
#include "Core/Player.h"

namespace core {

    TEST(PlayerTest, DefaultConstructor) {
        Player player;
        EXPECT_EQ(player.getName(), "");
        EXPECT_EQ(player.getSurname(), "");
        EXPECT_EQ(player.getAge(), 0);
        EXPECT_EQ(player.getHeight(), 0);
        EXPECT_EQ(player.getWeight(), 0);
        EXPECT_EQ(player.getGameNumber(), 0);
        EXPECT_EQ(player.getCountryName(), "");
    }

    TEST(PlayerTest, ParameterizedConstructor) {
        Player player("John", "Doe", 25, 180, 75, 10, "USA");
        EXPECT_EQ(player.getName(), "John");
        EXPECT_EQ(player.getSurname(), "Doe");
        EXPECT_EQ(player.getAge(), 25);
        EXPECT_EQ(player.getHeight(), 180);
        EXPECT_EQ(player.getWeight(), 75);
        EXPECT_EQ(player.getGameNumber(), 10);
        EXPECT_EQ(player.getCountryName(), "USA");
    }

} // namespace core
