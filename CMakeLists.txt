cmake_minimum_required(VERSION 3.10)
project(SportRoster)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(lib/googletest)

set(SOURCES 
    "src/main.cpp"

    "consoleGUI/buttons.cpp"
    "consoleGUI/colors.cpp"
    "consoleGUI/cursor.cpp"
    "consoleGUI/Object.cpp"
    "consoleGUI/window.cpp"

    "src/Core/ApplicationCore.cpp"
    "src/Core/Player.cpp"
    "src/Core/Team.cpp"

    "src/Menu/MainMenu.cpp"
    "src/Menu/TUIMenuFactory.cpp"

    "src/UI/TUI.cpp"
    "src/UI/UI.cpp"
)

set(HEADERS 
    "src/Application.h"

    "consoleGUI/GUI.h"
    "consoleGUI/buttons.h"
    "consoleGUI/colors.h"
    "consoleGUI/cursor.h"
    "consoleGUI/Object.h"
    "consoleGUI/window.h"

    "include/ApplicationCore.h"
    "include/IApplicationCore.h"
    "include/Player.h"
    "include/Team.h"

    "include/Menu.h"
    "include/MainMenu.h"
    "include/MenuFactory.h"
    "include/TUIMenuFactory.h"
    
    "include/TUI.h"
    "include/UI.h"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/consoleGUI)

add_subdirectory(tests)