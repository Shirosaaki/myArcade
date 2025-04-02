cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    arcade
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare ncurses library ----

add_library(arcade_ncurses SHARED
    lib/graphicals/ncurses/LibNcurses.cpp
    lib/graphicals/ncurses/LibNcurses.hpp
)

set_target_properties(arcade_ncurses PROPERTIES
    OUTPUT_NAME "arcade_ncurses"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
)

target_link_libraries(arcade_ncurses ncurses)

# ---- Declare SDL2 library ----

add_library(arcade_sdl2 SHARED
    lib/graphicals/sdl2/LibSDL2.cpp
    lib/graphicals/sdl2/LibSDL2.hpp
)

set_target_properties(arcade_sdl2 PROPERTIES
    OUTPUT_NAME "arcade_sdl2"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
target_include_directories(arcade_sdl2 PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
target_link_libraries(arcade_sdl2 PRIVATE SDL2_image SDL2_ttf SDL2 SDL2_mixer)

# ---- Declare SFMl library ----

add_library(arcade_sfml SHARED
    lib/graphicals/sfml/LibSfml.cpp
    lib/graphicals/sfml/LibSfml.hpp
)

set_target_properties(arcade_sfml PROPERTIES
    OUTPUT_NAME "arcade_sfml"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
)

find_package(SFML COMPONENTS graphics REQUIRED)
target_link_libraries(arcade_sfml PRIVATE sfml-graphics sfml-window sfml-audio)

# ---- Declare game menu library ----

add_library(arcade_menu SHARED
    lib/games/menu/GameMenu.cpp
    lib/games/menu/GameMenu.hpp
)

set_target_properties(arcade_menu PROPERTIES
    OUTPUT_NAME "arcade_menu"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
)

# ---- Declare pacman library ----

add_library(arcade_pacman SHARED
    lib/games/pacman/GamePacman.cpp
    lib/games/pacman/GamePacman.hpp
)

set_target_properties(arcade_pacman PROPERTIES
    OUTPUT_NAME "arcade_pacman"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
)

# ---- Declare snake library ----

add_library(arcade_snake SHARED
    lib/games/snake/GameSnake.cpp
    lib/games/snake/GameSnake.hpp
)

set_target_properties(arcade_snake PROPERTIES
    OUTPUT_NAME "arcade_snake"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
)

# ---- Declare the show library ----

add_library(arcade_show SHARED
    lib/games/theShow/GameTheShow.cpp
    lib/games/theShow/GameTheShow.hpp
)

set_target_properties(arcade_show PROPERTIES
    OUTPUT_NAME "arcade_the_show"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    PREFIX ""
)

# ---- Declare executable ----

add_executable(arcade_exe source/main.cpp source/GameCore.cpp source/Error.cpp)
add_executable(arcade::exe ALIAS arcade_exe)

set_property(TARGET arcade_exe PROPERTY OUTPUT_NAME arcade)

# Set the runtime output directory to the root of the project
set_target_properties(arcade_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_compile_features(arcade_exe PRIVATE cxx_std_20)

# ---- Install rules ----

install(TARGETS arcade_ncurses arcade_sdl2 arcade_sfml arcade_menu arcade_pacman arcade_snake
    LIBRARY DESTINATION lib
)

install(TARGETS arcade_exe
    RUNTIME DESTINATION bin
)

# ---- Developer mode ----

if(NOT arcade_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

include(cmake/dev-mode.cmake)