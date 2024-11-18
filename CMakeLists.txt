cmake_minimum_required(VERSION 3.10)
project(sagrada)


# Set the C standard
set(CMAKE_C_STANDARD 99)

# Add the executable
file(GLOB SOURCES "src/*.c")
add_executable(game ${SOURCES})

# Include directories
target_include_directories(game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


# Add compiler flags
target_compile_options(game PRIVATE -Werror -Wextra -g)
