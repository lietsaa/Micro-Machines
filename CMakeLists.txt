cmake_minimum_required (VERSION 3.11)

project(Micro-Machines)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories ("src")

add_executable(Micro-Machines src/main.cpp)

include (FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.x
)

FetchContent_MakeAvailable(sfml)
target_link_libraries(Micro-Machines sfml-graphics)


