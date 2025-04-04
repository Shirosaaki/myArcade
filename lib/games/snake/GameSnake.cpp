#include "GameSnake.hpp"
#include <ncurses.h>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

arcade::GameSnake::GameSnake() : score(0), direction(1)
{
    srand(time(0));
    snake.push_back(std::make_pair(10, 9));
    snake.push_back(std::make_pair(10, 8));
    snake.push_back(std::make_pair(10, 7));
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
            if (direction != 2) direction = 0;
            break;
        case arcade::KeyBind::RIGHT_KEY:
            if (direction != 3) direction = 1;
            break;
        case arcade::KeyBind::DOWN_KEY:
            if (direction != 0) direction = 2;
            break;
        case arcade::KeyBind::LEFT_KEY:
            if (direction != 1) direction = 3;
            break;
        default:
            break;
    }
}

int arcade::GameSnake::getScore()
{
    return 50;
}

std::string arcade::GameSnake::getSound(enum arcade::TGraphics lib)
{
    (void)lib;
    return "";
}

void arcade::GameSnake::resetGame()
{
    score = 0;
    direction = 1;
    snake.clear();
    snake.push_back(std::make_pair(10, 9));
    snake.push_back(std::make_pair(10, 8));
    snake.push_back(std::make_pair(10, 7));
}

extern "C" arcade::IGames *entryPoint() {
    return new arcade::GameSnake();
}
