cmake_minimum_required(VERSION 3.10)

# Set the project name
project(GameProject)

# Add the executable
add_executable(game
    board.c
    color.c
    die.c
    helper.c
    main.c
)

# Include directories
target_include_directories(game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
