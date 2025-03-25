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

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GameSnake::GetDisplay(enum arcade::TGraphics lib)
{
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;

    if (lib == arcade::TGraphics::NCURSES)
        entities["SNAKE"] = std::make_pair(std::make_pair(0, 0), std::make_pair(6, 6));
    else
        entities["assets/snake.png"] = std::make_pair(std::make_pair(0, 0), std::make_pair(50, 50));
    return entities;
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
