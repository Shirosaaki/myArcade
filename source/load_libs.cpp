/*
** EPITECH PROJECT, 2025
** load
** File description:
** load
*/
#include "my.hpp"

std::map<std::string, std::pair<arcade::TGraphics, arcade::IGraphics *>> loadGraphicalsLibs(const std::string &path, std::string lib)
{
    std::map<std::string, std::pair<arcade::TGraphics, arcade::IGraphics *>> libMap;
    arcade::IGraphics *graphics = getGraphicsLib(lib);
    if (graphics == nullptr)
        return libMap;
    libMap[lib] = std::make_pair(getLib(lib), graphics);

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string path = entry.path();
        if (path.find("lib/arcade_") == std::string::npos || path == lib)
            continue;
        arcade::TGraphics lib = getLib(path);
        if (lib == arcade::TGraphics::NONE)
            continue;
        arcade::IGraphics *graphics = getGraphicsLib(path);
        if (graphics == nullptr)
            continue;
        libMap[path] = std::make_pair(lib, graphics);
    }
    return libMap;
}

std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> loadGamesLibs(const std::string &path)
{
    std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> gameMap;
    arcade::IGames *game = getGameLib("lib/arcade_menu.so");
    if (game == nullptr)
        return gameMap;
    gameMap["lib/arcade_menu.so"] = std::make_pair(arcade::TGames::MENU, game);

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string path = entry.path();
        if (path.find("lib/arcade_") == std::string::npos)
            continue;
        arcade::TGames tgame = getGame(path);
        if (tgame == arcade::TGames::NONE)
            continue;
        arcade::IGames *game = getGameLib(path);
        if (game == nullptr)
            continue;
        gameMap[path] = std::make_pair(tgame, game);
    }
    return gameMap;
}
