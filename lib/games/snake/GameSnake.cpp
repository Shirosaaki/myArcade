/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/
#include "GameSnake.hpp"

arcade::GameSnake::GameSnake()
{
}

arcade::GameSnake::~GameSnake()
{
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplay(enum arcade::TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;

    if (lib == arcade::TGraphics::NCURSES)
        display.push_back(std::make_pair("SNAKE", std::make_pair(std::make_pair(0, 0), std::make_pair(6, 6))));
    else
        display.push_back(std::make_pair("SNAKE", std::make_pair(std::make_pair(390, 330), std::make_pair(280, 50))));
    return display;
}

void arcade::GameSnake::setKey(enum arcade::KeyBind key)
{
    switch (key) {
        case arcade::KeyBind::UP_KEY:
            if (direction != Direction::DOWN) direction = Direction::UP;
            break;
        case arcade::KeyBind::DOWN_KEY:
            if (direction != Direction::UP) direction = Direction::DOWN;
            break;
        case arcade::KeyBind::LEFT_KEY:
            if (direction != Direction::RIGHT) direction = Direction::LEFT;
            break;
        case arcade::KeyBind::RIGHT_KEY:
            if (direction != Direction::LEFT) direction = Direction::RIGHT;
            break;
        default:
            break;
    }
}

int arcade::GameSnake::getScore()
{
    return 0;
}

std::string arcade::GameSnake::getSound(enum arcade::TGraphics lib)
{
    (void)lib;
    return "";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GameSnake();
}
