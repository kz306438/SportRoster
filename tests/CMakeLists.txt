cmake_minimum_required(VERSION 3.10)

if(WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrtd")
endif()

add_executable(RosterTests 
    main.cpp
    PlayerTest.cpp
    StorageTest.cpp
    ${CMAKE_SOURCE_DIR}/src/Core/Player.cpp 
    ${CMAKE_SOURCE_DIR}/src/Core/Storage.cpp 
)   
 
target_include_directories(RosterTests PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(RosterTests gtest gtest_main)

add_test(NAME RosterTests COMMAND RosterTests)
