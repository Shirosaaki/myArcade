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
    void *handle = dlopen(lib.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen failed: " << dlerror() << std::endl;
        return nullptr;
    }
    arcade::IGraphics *(*entryPoint)();
    entryPoint = (arcade::IGraphics *(*)())dlsym(handle, "entryPoint");
    if (!entryPoint) {
        std::cerr << "dlsym failed: " << dlerror() << std::endl;
        return nullptr;
    }
    return entryPoint();
}

arcade::IGames *getGameLib(const std::string& lib)
{
    void *handle = dlopen(lib.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen failed: " << dlerror() << std::endl;
        return nullptr;
    }
    arcade::IGames *(*entryPoint)();
    entryPoint = (arcade::IGames *(*)())dlsym(handle, "entryPoint");
    if (!entryPoint) {
        std::cerr << "dlsym failed: " << dlerror() << std::endl;
        return nullptr;
    }
    return entryPoint();
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade path_to_graphical_lib" << std::endl;
        return 84;
    }
    arcade::TGraphics lib = getLib(av[1]);
    if (lib == arcade::TGraphics::NONE) {
        std::cerr << "Invalid graphical library" << std::endl;
        return 84;
    }
    std::map<std::string, std::pair<arcade::TGraphics, arcade::IGraphics *>> libMap;
    arcade::IGraphics *graphics = getGraphicsLib(av[1]);
    libMap[av[1]] = std::make_pair(lib, graphics);

    for (const auto &entry : std::filesystem::directory_iterator("lib")) {
        std::string path = entry.path();
        if (path.find("lib/arcade_") == std::string::npos || 
            path == av[1]) {
            continue;
        }
        arcade::TGraphics lib = getLib(path);
        if (lib == arcade::TGraphics::NONE) {
            continue;
        }
        arcade::IGraphics *graphics = getGraphicsLib(path);
        libMap[path] = std::make_pair(lib, graphics);
    }
    arcade::IGames *game = getGameLib("lib/arcade_menu.so");
    std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> gameMap;
    gameMap["lib/arcade_menu.so"] = std::make_pair(arcade::TGames::MENU, game);
    for (const auto &entry : std::filesystem::directory_iterator("lib")) {
        std::string path = entry.path();
        if (path.find("lib/") == std::string::npos) {
            continue;
        }
        arcade::TGames tgame = getGame(path);
        if (tgame == arcade::TGames::NONE) {
            continue;
        }
        arcade::IGames *game = getGameLib(path);
        gameMap[path] = std::make_pair(tgame, game);
    }
    std::string actLib = av[1];
    std::string actGame = "lib/arcade_menu.so";

    while (1) {
        auto entities = game->GetDisplay(lib);
        graphics->Display(entities);
        auto key = graphics->getKey();
        if (key == arcade::KeyBind::ESC) {
            graphics->Nuke();
            break;
        } if (key == arcade::KeyBind::Z_KEY) {
            auto it = libMap.find(actLib);
            if (it != libMap.end()) {
                ++it;
                if (it == libMap.end())
                    it = libMap.begin();
                actLib = it->first;
                graphics->Nuke();
                graphics = it->second.second;
                graphics->Init();
                lib = it->second.first;
            }

        }
    }
}
