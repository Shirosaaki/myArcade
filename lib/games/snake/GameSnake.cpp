/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/

#include "GameSnake.hpp"
#include <unistd.h>

arcade::GameSnake::GameSnake() : score(0), direction(RIGHT), wall(std::make_pair(70, 35)), offset_pos(std::make_pair(0, 0)), gameOver(false), isGraphic(false)
{
    snake.clear();
    initialized = false;
    int width_screen = 184;
    int height_screen = 45;
    
    offset_pos = std::make_pair((height_screen - wall.second) / 2, (width_screen - wall.first) / 2);

    offset_posGraph = std::make_pair((720 - wall.second * 8) / 2, (510 - wall.first * 8) / 2);

    generateFruit();
    generateFruitGraph();

}

arcade::GameSnake::~GameSnake()
{
}

void arcade::GameSnake::generateMap(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    int width_screen = 184;
    int height_screen = 45;
    
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

void arcade::GameSnake::generateMapGraph(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    int width_screen = 720;
    int height_screen = 510;
    
    offset_pos = std::make_pair((height_screen - wall.second * 8) / 2, (width_screen - wall.first * 8) / 2);
    
    for (int x = 0; x < wall.first * 8; x++) {
        entities.push_back(std::make_pair("assets/Snake/wall.png", std::make_pair(std::make_pair(offset_pos.first, offset_pos.second + x), std::make_pair(15, 15))));
        entities.push_back(std::make_pair("assets/Snake/wall.png", std::make_pair(std::make_pair(offset_pos.first + wall.second * 8 - 1, offset_pos.second + x), std::make_pair(15, 15))));
    }
    for (int y = 0; y < wall.second * 8; y++) {
        entities.push_back(std::make_pair("assets/Snake/wall.png", std::make_pair(std::make_pair(offset_pos.first + y, offset_pos.second), std::make_pair(15, 15))));
        entities.push_back(std::make_pair("assets/Snake/wall.png", std::make_pair(std::make_pair(offset_pos.first + y, offset_pos.second + wall.first * 8 - 1), std::make_pair(15, 15))));
    }
}

bool arcade::GameSnake::isGameOver() {
    return gameOver;
}

void arcade::GameSnake::generateFruitGraph() {
    int minX = offset_pos.first + 10;
    int maxX = offset_pos.first + (wall.second * 8) - 20;
    int minY = offset_pos.second + 10;
    int maxY = offset_pos.second + (wall.first * 8) - 20;
    
    int gridWidth = (maxX - minX) / 10;
    int gridHeight = (maxY - minY) / 10;
    
    int gridPosX = rand() % gridWidth;
    int gridPosY = rand() % gridHeight;
    
    appleGraph.first = minX + gridPosX * 10 + 10;
    appleGraph.second = minY + gridPosY * 10 + 10;
    
    for (const auto& segment : snake) {
        if (segment.first == appleGraph.first && segment.second == appleGraph.second) {
            generateFruitGraph();
            return;
        }
    }
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
    void arcade::GameSnake::initSnake()
    {
        if (!initialized && isGraphic == false) {
            snake.clear(); 
            snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + (wall.first) / 2));
            snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + (wall.first) / 2 - 1));
            snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + (wall.first) / 2 - 2));
        }
        if (!initialized && isGraphic == true) {
            snake.clear(); 
            snake.push_back(std::make_pair(offset_pos.first + (wall.second * 8) / 2, offset_pos.second + (wall.first * 8) / 2));
            snake.push_back(std::make_pair(offset_pos.first + (wall.second * 8) / 2, offset_pos.second + (wall.first * 8) / 2 - 10));
            snake.push_back(std::make_pair(offset_pos.first + (wall.second * 8) / 2, offset_pos.second + (wall.first * 8) / 2 - 20));
        }
        initialized = true;

    }

    void arcade::GameSnake::updateGameGraph(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities) {
        generateMapGraph(entities);
        
        initSnake();
        
        for (size_t i = snake.size() - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
        }
        
        switch (direction) {
            case UP:
            snake[0].second -= 10;
            break;
            case RIGHT:
            snake[0].first += 10;
            break;
            case DOWN:
            snake[0].second += 10;
            break;
            case LEFT:
            snake[0].first -= 10;
            break;
        }
        
        if ((abs(snake[0].first - appleGraph.first) < 10 && abs(snake[0].second - appleGraph.second) < 10)) {
            snake.push_back(snake.back());
            score += 10;
            generateFruitGraph();
        }
        
        int i = 0;
        for (const auto& segment : snake) {
            if (i == 0) {
                entities.push_back(std::make_pair("assets/Snake/head.png*", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(10, 10))));
                i++;
                continue;
            }
            entities.push_back(std::make_pair("assets/Snake/body.png*" + std::to_string(i), std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(10, 10))));
            i++;
        }
        entities.push_back(std::make_pair("assets/Snake/apple.png", std::make_pair(std::make_pair(appleGraph.first, appleGraph.second), std::make_pair(10, 10))));
    }
    
    void arcade::GameSnake::updateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities) {
        generateMap(entities);
        initSnake();
        
        for (size_t i = snake.size() - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
        }
        
        switch (direction) {
            case UP:
            snake[0].first--;
            break;
            case RIGHT:
            snake[0].second++;
            break;
            case DOWN:
            snake[0].first++;
            break;
            case LEFT:
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
    
    void arcade::GameSnake::resetGame()
    {
        score = 0;
        direction = RIGHT;
        gameOver = false;
        snake.clear();
        initialized = false;
        
        snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2));
        snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2 - 1));
        snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2 - 2));
        
        generateFruit();
    }
    
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplay(enum arcade::TGraphics lib)
    {
        std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;
        
        if (lib == arcade::TGraphics::NCURSES) {
            return GetDisplayNcurses();
        } else
            return GetDisplayGraph();
        return display;
    }
    
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplayNcurses()
    {
        std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;
        
        if (isGameOver()) {
            getActGame();
        }
        if (key != arcade::KeyBind::NONE) {
            setKey(key);
        }
        display.push_back(std::make_pair("*clear", std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
        display.push_back(std::make_pair("Score:" + std::to_string(score), std::make_pair(std::make_pair(4, 57), std::make_pair(6, 6))));
        updateGame(display);
        usleep(129000);
        return display;
}



std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplayGraph()
{
    isGraphic = true;
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;
    display.push_back(std::make_pair("Score: " + std::to_string(score), std::make_pair(std::make_pair(100, 20), std::make_pair(200, 50))));
    updateGameGraph(display);    
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
    this->key = key;
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

std::string arcade::GameSnake::getActGame()
{
    if (gameOver == true) {
        return "Game Over";
    }
    return "Game Snake";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GameSnake();
}
