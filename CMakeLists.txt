cmake_minimum_required(VERSION 3.16)
project(DanganStarFall VERSION 1.0 LANGUAGES C CXX)

# Set CXX standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files
file(GLOB_RECURSE SOURCES
    "*.cxx"
    "Scenes/*.cxx"
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

set(BUILD_DEMOS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/pebble/external/chipmunk)

add_subdirectory(external/discord-presence)
# target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/DiscordRPC)
# target_link_libraries(${PROJECT_NAME} PRIVATE discord-rpc)

find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_link_libraries(${PROJECT_NAME} PRIVATE chipmunk m)
target_link_libraries(${PROJECT_NAME} PRIVATE discord-rpc m)

target_include_directories(DanganStarFall PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/FraxFramework
    ${CMAKE_SOURCE_DIR}/external/pebble 
    ${CMAKE_SOURCE_DIR}/external/pebble/external/chipmunk/include
    ${CMAKE_SOURCE_DIR}/external/discord-presence/include
    ${CMAKE_SOURCE_DIR}/external/raygui/src
)

# Optional: enable compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX -g)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -g)
endif()

# Set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
