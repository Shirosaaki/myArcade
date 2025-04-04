/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/

#include "GameSnake.hpp"
#include <unistd.h>

arcade::GameSnake::GameSnake() : score(0), direction(RIGHT), wall(std::make_pair(70, 35)), offset_pos(std::make_pair(0, 0)), gameOver(false)
{
    // snake.push_back(std::make_pair(20, 75));
    // snake.push_back(std::make_pair(20, 76));
    // snake.push_back(std::make_pair(20, 77));
    snake.clear();
    fruit = std::make_pair(10, 80);
    initialized = false;
}

arcade::GameSnake::~GameSnake()
{
}



void arcade::GameSnake::generateMap(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    int width_screen = 0;
    int height_screen = 0;
    getmaxyx(stdscr, height_screen, width_screen);
    
    
    offset_pos = std::make_pair((height_screen - wall.second) / 2, (width_screen - wall.first) / 2);
    
    for (int x = 0; x < wall.first; x++) {
        entities.push_back(std::make_pair("#*wall_up", std::make_pair(std::make_pair(offset_pos.first, offset_pos.second + x), std::make_pair(4, 4))));
        entities.push_back(std::make_pair("#*wall_down", std::make_pair(std::make_pair(offset_pos.first + wall.second - 1, offset_pos.second + x), std::make_pair(4, 4))));
    }
    for (int y = 0; y < wall.second; y++) {
        entities.push_back(std::make_pair("#*wall_left", std::make_pair(std::make_pair(offset_pos.first + y, offset_pos.second), std::make_pair(4, 4))));
        entities.push_back(std::make_pair("#*wall_right", std::make_pair(std::make_pair(offset_pos.first + y, offset_pos.second + wall.first - 1), std::make_pair(4, 4))));
    }
}

bool arcade::GameSnake::isGameOver() {
    return gameOver;
}

void arcade::GameSnake::generateFruit() {
    fruit.first = offset_pos.first + 1 + rand() % (wall.second - 2);
    fruit.second = offset_pos.second + 1 + rand() % (wall.first - 2);
    for (const auto& segment : snake) {
        if (segment == fruit) {
            generateFruit();
            return;
        }
    }
}

void arcade::GameSnake::checkCollision(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities)
{
    if (snake[0].first <= offset_pos.first || snake[0].first >= offset_pos.first + wall.second ||
        snake[0].second <= offset_pos.second || snake[0].second >= offset_pos.second + wall.first) {
        gameOver = true;
    }
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[0] == snake[i]) {
            gameOver = true;
        }
    }
}
    
    void arcade::GameSnake::updateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities) {
        generateMap(entities);
        
        if (!initialized) {
            snake.clear(); 
            snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2));
            snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2 - 1));
            snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2 - 2));
            initialized = true;
        }
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

        int i = 0;
        for (const auto& segment : snake) {
            if (i == 0) {
                entities.push_back(std::make_pair("$*head", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(1, 1))));
                i++;
                continue;
            }
            auto key = std::to_string(i);
            entities.push_back(std::make_pair("O*" + key, std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(2, 2))));
            i++;
        }
        entities.push_back(std::make_pair("A*fruit", std::make_pair(std::make_pair(fruit.first, fruit.second), std::make_pair(3, 3))));

        checkCollision(entities);
    }
    
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplay(enum arcade::TGraphics lib)
    {
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;
    
    if (lib == arcade::TGraphics::NCURSES) {
        display.push_back(std::make_pair("Score:", std::make_pair(std::make_pair(4, 57), std::make_pair(6, 6))));
        arcade::KeyBind key = ncurses.getKey();
        if (key != arcade::KeyBind::NONE) {
            setKey(key);
        }
        updateGame(display);
        if (isGameOver()) {
            display.clear();
            display.push_back(std::make_pair("GAME OVER", std::make_pair(std::make_pair(5, 60), std::make_pair(5, 5))));
            display.push_back(std::make_pair("RESTART", std::make_pair(std::make_pair(10, 45), std::make_pair(5, 5)))); 
            display.push_back(std::make_pair("QUIT", std::make_pair(std::make_pair(10, 75), std::make_pair(5, 5))));
        }
        usleep(129000);
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
    return score;
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