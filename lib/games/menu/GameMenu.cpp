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
        std::pair<std::pair<int, int>, std::pair<int, int>> entity = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
        std::pair<int, int> pos = std::make_pair(0, 0);
        std::pair<int, int> size = std::make_pair(0, 0);
        entities["menu"] = entity;
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
