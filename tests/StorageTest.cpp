#include <gtest/gtest.h>
#include "Core/Storage.h"
#include <filesystem>

namespace fs = std::filesystem;

class StorageTest : public ::testing::Test {
protected:
    std::string testDir = "test_storage";
    core::Storage storage{ testDir };

    void SetUp() override {
        if (fs::exists(testDir)) {
            fs::remove_all(testDir);
        }
        fs::create_directories(testDir);
    }

    void TearDown() override {
        if (fs::exists(testDir)) {
            fs::remove_all(testDir);
        }
    }
};

TEST_F(StorageTest, CreateFile) {
    std::string filename = "team1.txt";

    storage.createFile(filename);
    
    EXPECT_TRUE(fs::exists(testDir + "/" + filename));
}

TEST_F(StorageTest, AddContent) {
    std::string filename = "team2.txt";
    storage.createFile(filename);
    core::File—ontent content = { "Player1", "Player2" };
    
    storage.addContent(filename, content);
    auto readContent = storage.getContent(filename);
    
    EXPECT_EQ(readContent, content);
}

TEST_F(StorageTest, GetContent) {
    std::string filename = "team3.txt";
    storage.createFile(filename);
    core::File—ontent content = { "Captain", "Striker", "Defender" };
    
    storage.addContent(filename, content);

    EXPECT_EQ(storage.getContent(filename), content);
}

TEST_F(StorageTest, GetFiles) {
    storage.createFile("file1.txt");
    storage.createFile("file2.txt");
    
    auto files = storage.getFiles();
    
    EXPECT_EQ(files.size(), 2);
    EXPECT_NE(std::find(files.begin(), files.end(), "file1.txt"), files.end());
    EXPECT_NE(std::find(files.begin(), files.end(), "file2.txt"), files.end());
}
