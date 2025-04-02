/*
** EPITECH PROJECT, 2025
** GameCore
** File description:
** GameCore
*/
#ifndef GAME_CORE_HPP_
    #define GAME_CORE_HPP_
    #include "Error.hpp"
    #include <iostream>
    #include <string>
    #include <dlfcn.h>
    #include <map>
    #include "../lib/graphicals/IGraphics.hpp"
    #include "../lib/games/IGames.hpp"
    #include "../lib/games/menu/GameMenu.hpp"
    #include <filesystem>
    #include <fstream>

class GameCore {
    public:
        GameCore();
        ~GameCore();
        void loadGraphicalsLibs(const std::string &path, std::string lib);
        void loadGamesLibs(const std::string &path);
        arcade::TGraphics getLib(const std::string& lib);
        arcade::TGames getGame(const std::string& lib);
        arcade::IGraphics *getGraphicsLib(const std::string &path);
        arcade::IGames *getGameLib(const std::string &path);

        void setCurrentGraphical(const std::string &lib);
        void setCurrentGame(const std::string &lib);
        void setTypeCurrentGame(arcade::TGames type) { typeCurrentGame = type; }
        void setTypeCurrentGraphical(arcade::TGraphics type) { typeCurrentGraphical = type; }

        arcade::IGraphics *getCurrentGraphical() const { return _currentGraphical; }
        arcade::IGames *getCurrentGame() const { return _currentGame; }

        void konamiCode();

        void run();
        void nextGraphical();
        void prevGraphical();
        void nextGame();
        void prevGame();

    private:
        std::map<std::string, std::pair<arcade::TGraphics, arcade::IGraphics *>> _graphicals;
        std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> _games;
        arcade::IGraphics *_currentGraphical;
        arcade::IGames *_currentGame;
        arcade::TGames typeCurrentGame;
        arcade::TGraphics typeCurrentGraphical;
        std::vector<void *> _handles;
        std::vector<arcade::KeyBind> _konamiCode;
};

#endif /* !GAME_CORE_HPP_ */
