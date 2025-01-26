cmake_minimum_required(VERSION 3.10)
project(sagrada)


# Set the C standard
set(CMAKE_C_STANDARD 99)

# Add the executable
file(GLOB_RECURSE SOURCES "src/**/*.c" "src/*.c")
add_executable(sagrada ${SOURCES})


set(INCLUDE_DIRS "")
foreach(FILE ${SOURCES})
    get_filename_component(DIR ${FILE} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# Add include directories
target_include_directories(sagrada PRIVATE ${INCLUDE_DIRS})


# Add compiler flags
target_compile_options(sagrada PRIVATE -Wall -Werror -Wextra -g -fanalyzer)
