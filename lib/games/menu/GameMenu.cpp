/*
** EPITECH PROJECT, 2025
** game
** File description:
** game
*/
#include "GameMenu.hpp"

arcade::GameMenu::GameMenu()
{
}

arcade::GameMenu::~GameMenu()
{
}

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GameMenu::GetDisplay(enum TGraphics lib)
{
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;
    if (lib == TGraphics::NCURSES) {
        std::pair<std::pair<int, int>, std::pair<int, int>> entity = std::make_pair(std::make_pair(0, 50), std::make_pair(30, 30));
        entities["MENU"] = entity;

        std::pair<std::pair<int, int>, std::pair<int, int>> gamesBtn = std::make_pair(std::make_pair(3, 50), std::make_pair(20, 20));
        entities["GAMES:"] = gamesBtn;

        std::pair<std::pair<int, int>, std::pair<int, int>> snakeBtn = std::make_pair(std::make_pair(10, 25), std::make_pair(10, 10));
        entities["----> SNAKE"] = snakeBtn;

        std::pair<std::pair<int, int>, std::pair<int, int>> pacmanBtn = std::make_pair(std::make_pair(10, 75), std::make_pair(10, 10));
        entities["PACMAN"] = pacmanBtn;
    } else {
        std::pair<std::pair<int, int>, std::pair<int, int>> entity;
        entity.first = std::make_pair(0, 0);
        entity.second = std::make_pair(1080, 720);
        entities["assets/menu/menu.png"] = entity;
    }
    return entities;
}

void arcade::GameMenu::setKey(enum KeyBind key)
{
    (void)key;
}

int arcade::GameMenu::getScore()
{
    return 0;
}

std::string arcade::GameMenu::getSound(enum TGraphics lib)
{
    (void)lib;
    return "";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GameMenu();
}
