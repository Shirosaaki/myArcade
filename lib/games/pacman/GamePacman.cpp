/*
** EPITECH PROJECT, 2025
** GamePacman
** File description:
** GamePacman
*/
#include "GamePacman.hpp"

arcade::GamePacman::GamePacman()
{
}

arcade::GamePacman::~GamePacman()
{
}

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GamePacman::GetDisplay
(enum arcade::TGraphics lib)
{
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;

    if (lib == arcade::TGraphics::NCURSES)
        entities["PACMAN"] = std::make_pair(std::make_pair(0, 0), std::make_pair(6, 6));
    else
        entities["assets/pacman.png"] = std::make_pair(std::make_pair(0, 0), std::make_pair(50, 50));
    return entities;
}

void arcade::GamePacman::setKey(enum arcade::KeyBind key)
{
    (void)key;
}

int arcade::GamePacman::getScore()
{
    return 0;
}

std::string arcade::GamePacman::getSound(enum arcade::TGraphics lib)
{
    (void)lib;
    return "";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GamePacman();
}
