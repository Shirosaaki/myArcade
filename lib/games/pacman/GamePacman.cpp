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

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GamePacman::GetDisplay(enum arcade::TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;

    if (lib == arcade::TGraphics::NCURSES)
        display.push_back(std::make_pair("PACMAN", std::make_pair(std::make_pair(0, 0), std::make_pair(6, 6))));
    else
        display.push_back(std::make_pair("PACMAN", std::make_pair(std::make_pair(390, 330), std::make_pair(280, 50))));
    return display;
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
