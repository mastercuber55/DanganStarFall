cmake_minimum_required(VERSION 3.16)
project(DanganStarFall VERSION 1.0 LANGUAGES C CXX)

# Set CXX standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files
set(SOURCES
    main.cxx
    # Scenes/SceneTouchControls.cxx
    Scenes/SceneGame.cxx
    Classes/Bullet.cxx
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

find_library(CHIPMUNK_LIB chipmunk REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CHIPMUNK_LIB} m)

target_include_directories(DanganStarFall PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/FraxFramework
    ${CMAKE_SOURCE_DIR}/external/pebble 
)

# Optional: enable compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
