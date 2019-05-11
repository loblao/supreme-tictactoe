cmake_minimum_required(VERSION 3.1)

project(SupremeTicTacToe)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_library(SDL2TTF_LIB
             NAMES SDL2_ttf
             HINTS "C:\\SDL2-2.0.9\\lib\\x86" # XXX
)

add_executable(SupremeTicTacToe
    main.cxx
    window.cxx
    object.cxx
    grid.cxx
    superGrid.cxx
    controller.cxx
    gameOverObject.cxx
)
target_link_libraries(SupremeTicTacToe ${SDL2TTF_LIB} ${SDL2_LIBRARIES})
