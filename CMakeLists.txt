cmake_minimum_required(VERSION 3.10)
project(SportRoster)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(lib/googletest)

set(SOURCES 
    "src/main.cpp"
    "src/Application.cpp"

    "consoleGUI/buttons.cpp"
    "consoleGUI/colors.cpp"
    "consoleGUI/cursor.cpp"
    "consoleGUI/Object.cpp"
    "consoleGUI/window.cpp"

    "src/Core/ApplicationCore.cpp"
    "src/Core/Player.cpp"
    "src/Core/Team.cpp"
    "src/Core/Storage.cpp"
    "src/Core/Utils.cpp"

    "src/Menu/MainMenu.cpp"
    "src/Menu/CreateMenu.cpp"
    "src/Menu/TUIMenuFactory.cpp"

    "src/UI/TUI.cpp"
    "src/UI/UI.cpp"
    "src/UI/ConsoleManager.cpp"
    "src/UI/UIFactory.cpp"
    "src/UI/EditBox.cpp"
    "src/UI/EditLine.cpp"

    "src/Message/ConfirmMSG.cpp"
)

set(HEADERS 
    "src/Application.h"

    "consoleGUI/GUI.h"
    "consoleGUI/buttons.h"
    "consoleGUI/colors.h"
    "consoleGUI/cursor.h"
    "consoleGUI/Object.h"
    "consoleGUI/window.h"

    "include/Core/ApplicationCore.h"
    "include/Core/Player.h"
    "include/Core/Team.h"
    "include/Core/Storage.h"
    "include/Core/Utils.h"
    "include/Core/Sort.h"

    "include/Menu/Menu.h"
    "include/Menu/MainMenu.h"
    "include/Menu/CreateMenu.h"
    "include/Menu/MenuFactoryFactory.h"
    "include/Menu/TUIMenuFactory.h"
    "include/Menu/MenuFactory.h"
    "include/Menu/MenuType.h"
    
    "include/UI/TUI.h"
    "include/UI/UI.h"
    "include/UI/ConsoleManager.h"
    "include/UI/UIFactory.h"
    "include/UI/UIType.h"
    "include/UI/Widgets/EditBox.h"
    "include/UI/Widgets/EditLine.h"

    "include/Message/Message.h"
    "include/Message/ConfirmMSG.h"
   

)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/consoleGUI)

add_subdirectory(tests)