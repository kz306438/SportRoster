cmake_minimum_required(VERSION 3.10)
project(SportRoster)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)

file(GLOB_RECURSE CORE_SRC src/Core/*.cpp)
file(GLOB_RECURSE CORE_HEADERS src/Core/*.h)

file(GLOB_RECURSE MENU_SRC src/Menu/*.cpp)
file(GLOB_RECURSE MENU_HEADERS src/Menu/*.h)

file(GLOB_RECURSE UI_SRC src/UI/*.cpp)
file(GLOB_RECURSE UI_HEADERS src/UI/*.h)

file(GLOB_RECURSE CONSOLE_GUI_SRC src/consoleGUI/*.cpp)
file(GLOB_RECURSE CONSOLE_GUI_HEADERS src/consoleGUI/*.h)

set(MAIN_SRC src/main.cpp)

add_executable(SportRoster ${MAIN_SRC} 
    ${CORE_SRC} ${CORE_HEADERS}
    ${MENU_SRC} ${MENU_HEADERS}
    ${UI_SRC} ${UI_HEADERS}
    ${CONSOLE_GUI_SRC} ${CONSOLE_GUI_HEADERS}
)
if (MSVC)
    target_compile_options(SportRoster PRIVATE /W4)
else()
    target_compile_options(SportRoster PRIVATE -Wall -Wextra -pedantic -O2)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_source_files_properties(${CORE_HEADERS} ${MENU_HEADERS} ${UI_HEADERS} ${CONSOLE_GUI_HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE)
