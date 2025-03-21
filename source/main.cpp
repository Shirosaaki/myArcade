#include <iostream>
#include <string>
#include <dlfcn.h>
#include <map>
#include "../lib/graphicals/IGraphics.hpp"
#include "../lib/games/IGames.hpp"
#include <filesystem>
#include <fstream>

arcade::TGraphics getLib(const std::string& lib)
{
    static const std::map<std::string, arcade::TGraphics> libMap = {
        {"lib/arcade_ncurses.so", arcade::TGraphics::NCURSES},
        {"lib/arcade_sdl2.so", arcade::TGraphics::SDL},
        {"lib/arcade_ndk++.so", arcade::TGraphics::NDK},
        {"lib/arcade_aalib.so", arcade::TGraphics::AA},
        {"lib/arcade_libcaca.so", arcade::TGraphics::CACA},
        {"lib/arcade_allegro5.so", arcade::TGraphics::ALLEGRO},
        {"lib/arcade_xlib.so", arcade::TGraphics::X},
        {"lib/arcade_gtk+.so", arcade::TGraphics::GTK},
        {"lib/arcade_sfml.so", arcade::TGraphics::SFML},
        {"lib/arcade_irrlicht.so", arcade::TGraphics::IRRLICHT},
        {"lib/arcade_opengl.so", arcade::TGraphics::OPENGL},
        {"lib/arcade_vulkan.so", arcade::TGraphics::VULKAN},
        {"lib/arcade_qt.so", arcade::TGraphics::QT}
    };
    auto it = libMap.find(lib);
    return (it != libMap.end()) ? it->second : arcade::TGraphics::NONE;
}

arcade::TGames getGame(const std::string& lib)
{
    static const std::map<std::string, arcade::TGames> gameMap = {
        {"lib/snake.so", arcade::TGames::SNAKE},
        {"lib/minesweeper.so", arcade::TGames::MINESWEEPER},
        {"lib/nibbler.so", arcade::TGames::NIBBLER},
        {"lib/pacman.so", arcade::TGames::PACMAN},
        {"lib/qix.so", arcade::TGames::QIX},
        {"lib/centipede.so", arcade::TGames::CENTIPEDE},
        {"lib/solarfox.so", arcade::TGames::SOLARFOX},
        {"lib/sokoban.so", arcade::TGames::SOKOBAN},
        {"lib/space_invader.so", arcade::TGames::SPACE_INVADER},
        {"lib/tetris.so", arcade::TGames::TETRIS},
        {"lib/the_show.so", arcade::TGames::THE_SHOW},
        {"lib/menu.so", arcade::TGames::MENU}
    };
    auto it = gameMap.find(lib);
    return (it != gameMap.end()) ? it->second : arcade::TGames::NONE;
}

arcade::IGraphics *getGraphicsLib(const std::string& lib)
{
    return 0;
}
