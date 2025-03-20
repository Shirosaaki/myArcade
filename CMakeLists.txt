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
)

find_package(SDL2 REQUIRED)
target_include_directories(arcade_sdl2 PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(arcade_sdl2 ${SDL2_LIBRARIES})

# ---- Declare executable ----

add_executable(arcade_exe source/main.cpp)
add_executable(arcade::exe ALIAS arcade_exe)

set_property(TARGET arcade_exe PROPERTY OUTPUT_NAME arcade)

target_compile_features(arcade_exe PRIVATE cxx_std_20)

# Remove arcade_lib linkage
# target_link_libraries(arcade_exe PRIVATE arcade_lib)

# ---- Install rules ----

install(TARGETS arcade_ncurses arcade_sdl2
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