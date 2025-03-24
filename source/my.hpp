/*
** EPITECH PROJECT, 2025
** my
** File description:
** my
*/
#ifndef MY_HPP_
    #define MY_HPP_
    #include <iostream>
    #include <string>
    #include <dlfcn.h>
    #include <map>
    #include "../lib/graphicals/IGraphics.hpp"
    #include "../lib/games/IGames.hpp"
    #include "../lib/games/menu/GameMenu.hpp"
    #include <filesystem>
    #include <fstream>

std::map<std::string, std::pair<arcade::TGraphics, arcade::IGraphics *>> loadGraphicalsLibs(const std::string &path, std::string lib);
std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> loadGamesLibs(const std::string &path);
arcade::TGraphics getLib(const std::string &lib);
arcade::TGames getGame(const std::string &lib);
arcade::IGraphics *getGraphicsLib(const std::string& lib);
arcade::IGames *getGameLib(const std::string& lib);

#endif /* !MY_HPP_ */
