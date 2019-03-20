cmake_minimum_required(VERSION 3.0)

project(SupremeTicTacToe)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SupremeTicTacToe
    main.cxx
    window.cxx
    object.cxx
    grid.cxx
    superGrid.cxx
    controller.cxx
    gameOverObject.cxx
)
target_link_libraries(SupremeTicTacToe SDL2_ttf ${SDL2_LIBRARIES})
