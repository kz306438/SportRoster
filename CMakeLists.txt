cmake_minimum_required(VERSION 3.10)
project(SportRoster)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# === consoleGUI ===
file(GLOB_RECURSE CONSOLE_GUI_SRC src/consoleGUI/*.cpp src/consoleGUI/*.h)
add_library(consoleGUI ${CONSOLE_GUI_SRC})
target_include_directories(consoleGUI PRIVATE src/consoleGUI)

# === ui ===
file(GLOB_RECURSE UI_SRC src/ui/*.cpp src/ui/*.h)
add_library(ui ${UI_SRC})
target_include_directories(ui PRIVATE src/ui)

# === Core ===
file(GLOB_RECURSE CORE_SRC src/Core/*.cpp src/Core/*.h)
add_library(core ${CORE_SRC})
target_include_directories(core PRIVATE src/Core)

# === Menu ===
file(GLOB_RECURSE MENU_SRC src/Menu/*.cpp src/Menu/*.h)
add_library(menu ${MENU_SRC})
target_include_directories(menu PRIVATE src/Menu)

# === Главный файл ===
add_executable(${PROJECT_NAME} src/main.cpp src/Application.h)
target_link_libraries(${PROJECT_NAME} consoleGUI ui core menu)

# === Подключаем Google Test ===
# Опция для тестов
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    
    add_subdirectory(test)
    
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    
    file(GLOB_RECURSE TEST_SOURCES test/*.cpp test/*.h)
    add_executable(runTests ${TEST_SOURCES})
    target_link_libraries(runTests consoleGUI ui core menu GTest::GTest GTest::Main)
    
    add_test(NAME AllTests COMMAND runTests)
endif()
