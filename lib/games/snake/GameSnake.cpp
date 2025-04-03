/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/

#include "GameSnake.hpp"
#include <unistd.h>

arcade::GameSnake::GameSnake() : score(0), direction(RIGHT)
{
    snake.push_back(std::make_pair(10, 9));
    snake.push_back(std::make_pair(10, 8));
    snake.push_back(std::make_pair(10, 7));
 
    generateFruit();
}

arcade::GameSnake::~GameSnake()
{
}


void arcade::GameSnake::generateFruit() {
    fruit = std::make_pair(rand() % 20, rand() % 20);
    for (const auto& segment : snake) {
        if (segment == fruit) {
            generateFruit();
            return;
        }
    }
}

void arcade::GameSnake::generateMap(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    // Dimensions de la map
    int width = 20;
    int height = 20;

    for (int x = 0; x < width; ++x) {
        entities.push_back(std::make_pair("#*wall", std::make_pair(std::make_pair(0, x), std::make_pair(4, 4))));
        entities.push_back(std::make_pair("#*wall", std::make_pair(std::make_pair(height - 1, x), std::make_pair(4, 4))));
    }
    for (int y = 0; y < height; ++y) {
        entities.push_back(std::make_pair("#*wall", std::make_pair(std::make_pair(y, 0), std::make_pair(4, 4))));
        entities.push_back(std::make_pair("#*wall", std::make_pair(std::make_pair(y, width - 1), std::make_pair(4, 4))));
    }
}

void arcade::GameSnake::updateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities) {
    
    entities.push_back(std::make_pair("*clear", std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));

    generateMap(entities);

    for (size_t i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    switch (direction) {
        case UP: // Haut
            snake[0].first--;
            break;
        case RIGHT: // Droite
            snake[0].second++;
            break;
            case DOWN: // Bas
            snake[0].first++;
            break;
        case LEFT: // Gauche
            snake[0].second--;
            break;
    }

    if (snake[0] == fruit) {
        snake.push_back(snake.back());
        score += 10;
        generateFruit();
    }
}



std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplay(enum arcade::TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;
    
    if (lib == arcade::TGraphics::NCURSES) {
        int i = 0;
        for (const auto& segment : snake) {
            if (i == 0) {
                display.push_back(std::make_pair("$*head", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(2, 2))));
                i++;
                continue;
            }
            auto key = std::to_string(i);
            display.push_back(std::make_pair("O*" + key, std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(1, 1))));
            i++;
        }
        display.push_back(std::make_pair("A*fruit", std::make_pair(std::make_pair(fruit.first, fruit.second), std::make_pair(3, 3))));
        arcade::KeyBind key = ncurses.getKey();
        if (key != arcade::KeyBind::NONE) {
            setKey(key);
        }
        updateGame(display);
        usleep(100000);
    } else
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