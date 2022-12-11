project(Micro-Machines)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

message(STATUS "BUILD directory is ${CMAKE_BINARY_DIR}")
message(STATUS "SRC directory is ${CMAKE_SOURCE_DIR}")

file(GLOB SOURCES_C "src/*.c")
file(GLOB SOURCES_CPP "src/*.cpp")
file(GLOB SOURCES_HPP "src/*.hpp")
file(GLOB SOURCES_H "src/*.h")

include_directories(/opt/homebrew/include)
include_directories(/opt/homebrew/lib)
include_directories(/Users/Koti/Downloads/Cpp_project)

set(SOURCES ${SOURCES_C} ${SOURCES_CPP} ${SOURCES_H} ${SOURCES_HPP})

add_executable(Micro-Machines src/main.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(Micro-Machines sfml-graphics)

if(MSVC)
    target_compile_options(Micro-Machines PRIVATE /Wall)
else()
    target_compile_options(Micro-Machines PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers)
endif()