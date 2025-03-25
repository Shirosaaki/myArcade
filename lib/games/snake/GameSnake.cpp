/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/
#include "GameSnake.hpp"
#include <ncurses.h>

arcade::GameSnake::GameSnake()
    : board(30, 65)
{
}

arcade::GameSnake::~GameSnake()
{
}

void arcade::GameSnake::handleGame()
{
    board.init();
    board.addAt(10, 10, '0');
    board.refresh();
}

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GameSnake::GetDisplay(enum arcade::TGraphics lib)
{
    int xMax;
    int yMax;
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;

    if (lib == arcade::TGraphics::NCURSES) {
        handleGame();
    } else
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
