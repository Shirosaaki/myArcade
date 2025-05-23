/*
** EPITECH PROJECT, 2025
** game
** File description:
** game
*/
#include "GameMenu.hpp"

arcade::GameMenu::GameMenu()
{
    this->actGame = "lib/arcade_menu.so";
}

arcade::GameMenu::~GameMenu()
{
}

std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> arcade::GameMenu::loadGamesLibs(const std::string &path)
{
    std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> gameMap;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string path = entry.path();
        if (path.find("lib/arcade_") == std::string::npos)
            continue;
        arcade::TGames tgame = getGame(path);
        if (tgame == arcade::TGames::NONE)
            continue;
        arcade::IGames *game = this->getGameLib(path);
        if (game == nullptr)
            continue;
        gameMap[path] = std::make_pair(tgame, game);
    }
    gameMap.erase("lib/arcade_menu.so");
    this->nbGames = gameMap.size();
    return gameMap;
}

arcade::IGames *arcade::GameMenu::getGameLib(const std::string& lib)
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

arcade::TGames arcade::GameMenu::getGame(const std::string& lib)
{
    static const std::map<std::string, arcade::TGames> gameMap = {
        {"lib/arcade_snake.so", arcade::TGames::SNAKE},
        {"lib/arcade_minesweeper.so", arcade::TGames::MINESWEEPER},
        {"lib/arcade_nibbler.so", arcade::TGames::NIBBLER},
        {"lib/arcade_pacman.so", arcade::TGames::PACMAN},
        {"lib/arcade_qix.so", arcade::TGames::QIX},
        {"lib/arcade_centipede.so", arcade::TGames::CENTIPEDE},
        {"lib/arcade_solarfox.so", arcade::TGames::SOLARFOX},
        {"lib/arcade_sokoban.so", arcade::TGames::SOKOBAN},
        {"lib/arcade_space_invader.so", arcade::TGames::SPACE_INVADER},
        {"lib/arcade_tetris.so", arcade::TGames::TETRIS},
        {"lib/arcade_the_show.so", arcade::TGames::THE_SHOW},
        {"lib/arcade_menu.so", arcade::TGames::MENU}
    };
    auto it = gameMap.find(lib);
    return (it != gameMap.end()) ? it->second : arcade::TGames::NONE;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameMenu::getDisplay(enum TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    this->gameMap = loadGamesLibs("lib/");
    if (lib == TGraphics::NCURSES) {
        std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entity;
        entity.first = "MENU";
        entity.second.first = std::make_pair(0, 0);
        entity.second.second = std::make_pair(6, 6);
        entities.push_back(entity);
        int i = 3;
        for (const auto &game : this->gameMap) {
            entity.first = game.first;
            entity.second.first = std::make_pair(i, 0);
            entity.second.second = std::make_pair(6, 6);
            if (i / 2 == cursor) {
                entity.second.second = std::make_pair(1, 1);
                this->actGame = game.first;
            }
            entities.push_back(entity);
            i += 2;
        }
        nbGames = gameMap.size();
    } else {
        std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entity;
        entity.first = "assets/menu/menu.png";
        entity.second.first = std::make_pair(0, 0);
        entity.second.second = std::make_pair(1080, 720);
        entities.push_back(entity);
        int i = 330;
        int x = 1;
        for (const auto &game : this->gameMap) {
            entity.first = game.first;
            entity.second.first = std::make_pair(390, i);
            entity.second.second = std::make_pair(280, 50);
            std::string gameName = game.first;
            if (x == cursor) {
                gameName = "*RED*" + game.first;
                this->actGame = game.first;
            }
            entity.first = gameName;
            entities.push_back(entity);
            i += 70;
            x++;
        }
    }
    return entities;
}

void arcade::GameMenu::setKey(enum KeyBind key)
{
    switch (key) {
    case KeyBind::UP_KEY:
        cursor--;
        break;
    case KeyBind::DOWN_KEY:
        cursor++;
        break;
    default:
        break;
    }
    if (cursor < 1)
        cursor = nbGames;
    if (cursor > nbGames)
        cursor = 1;
}

int arcade::GameMenu::getScore()
{
    return 0;
}

std::string arcade::GameMenu::getSound(enum TGraphics lib)
{
    if (lib == TGraphics::NCURSES)
        return "";
    return "assets/menu/TheShost.wav";
}

std::string arcade::GameMenu::getActGame()
{
    return this->actGame;
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GameMenu();
}
