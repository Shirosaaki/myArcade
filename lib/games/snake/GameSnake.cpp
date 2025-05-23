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

bool arcade::GameSnake::isGameOver()
{
    return gameOver;
}

void arcade::GameSnake::generateFruitGraph()
{
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
    
    for (const auto& segment : snake)
        if (segment.first == appleGraph.first && segment.second == appleGraph.second) {
            generateFruitGraph();
            return;
        }
}

void arcade::GameSnake::generateFruit() {
    fruit.first = offset_pos.first + 1 + rand() % (wall.second - 2);
    fruit.second = offset_pos.second + 1 + rand() % (wall.first - 2);
    for (const auto& segment : snake)
        if (segment == fruit) {
            generateFruit();
            return;
        }
}

void arcade::GameSnake::checkCollision()
{
    if (snake[0].first <= offset_pos.first || snake[0].first >= offset_pos.first + wall.second ||
        snake[0].second <= offset_pos.second || snake[0].second >= offset_pos.second + wall.first)
        gameOver = true;
    for (size_t i = 1; i < snake.size(); ++i)
        if (snake[0] == snake[i])
            gameOver = true;
}

void arcade::GameSnake::checkCollisionGraph()
{
    if (isGraphic == true) {
        if (snake[0].first <= offset_pos.first || snake[0].first >= offset_pos.first + wall.second * 8 ||
            snake[0].second <= offset_pos.second || snake[0].second >= offset_pos.second + wall.first * 8)
            gameOver = true;
        for (size_t i = 1; i < snake.size(); ++i)
            if (snake[0] == snake[i])
                gameOver = true;
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
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime).count();
    
    initSnake();
    bool first = true;
    for (const auto& segment : snake) {
        if (first == true) {
            if (direction == Direction::UP)
                entities.push_back(std::make_pair("assets/Snake/headU.png", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(10, 10))));
            else if (direction == Direction::DOWN)
                entities.push_back(std::make_pair("assets/Snake/headD.png", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(10, 10))));
            else if (direction == Direction::LEFT)
                entities.push_back(std::make_pair("assets/Snake/headL.png", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(10, 10))));
            else
                entities.push_back(std::make_pair("assets/Snake/headR.png", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(10, 10))));
            first = false;
        } else
            entities.push_back(std::make_pair("assets/Snake/body.png", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(10, 10))));
    }
    entities.push_back(std::make_pair("assets/Snake/apple.png", std::make_pair(std::make_pair(appleGraph.first, appleGraph.second), std::make_pair(10, 10))));
    
    if (elapsed < 100)
        return;
    lastMoveTime = now;
    for (size_t i = snake.size() - 1; i > 0; --i)
        snake[i] = snake[i - 1];
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
    checkCollisionGraph();
}
    
void arcade::GameSnake::updateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities) {
    generateMap(entities);
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime).count();

    initSnake();
    bool first = true;
    for (const auto& segment : snake) {
        if (first == true) {
            if (Direction::UP == direction)
                entities.push_back(std::make_pair("^", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(1, 1))));
            else if (Direction::DOWN == direction)
                entities.push_back(std::make_pair("v", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(1, 1))));
            else if (Direction::LEFT == direction)
                entities.push_back(std::make_pair("<", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(1, 1))));
            else
                entities.push_back(std::make_pair(">", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(1, 1))));
            first = false;
        } else
            entities.push_back(std::make_pair("O", std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(2, 2))));
    }
    entities.push_back(std::make_pair("A", std::make_pair(std::make_pair(fruit.first, fruit.second), std::make_pair(3, 3))));
    if (elapsed < 200)
        return;
    lastMoveTime = now;
    for (size_t i = snake.size() - 1; i > 0; --i)
        snake[i] = snake[i - 1];
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
    checkCollision();
}
    
void arcade::GameSnake::resetGame()
{
    score = 0;
    direction = RIGHT;
    gameOver = false;
    snake.clear();
    initialized = false;

    if (isGraphic)
        offset_pos = std::make_pair((510 - wall.first * 8) / 2, (720 - wall.second * 8) / 2);
    else
        offset_pos = std::make_pair((45 - wall.second) / 2, (184 - wall.first) / 2);
    snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2));
    snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2 - 1));
    snake.push_back(std::make_pair(offset_pos.first + wall.second / 2, offset_pos.second + wall.first / 2 - 2));
    if (isGraphic)
        generateFruitGraph();
    else
        generateFruit();
}
    
std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::getDisplay(enum arcade::TGraphics lib)
{
    if (isGraphic == true && lib == arcade::TGraphics::NCURSES) {
        isFruitGenerated = false;
        initialized = false;
    }
    else if (isGraphic == false && lib != arcade::TGraphics::NCURSES) {
        isFruitGenerated = false;
        initialized = false;
    }
    if (lib == arcade::TGraphics::NCURSES) {
        isGraphic = false;
        if (isFruitGenerated == false) {
            generateFruit();
            isFruitGenerated = true;
        }
        return GetDisplayNcurses();
    } else {
        isGraphic = true;
        if (isFruitGenerated == false) {
            generateFruitGraph();
            isFruitGenerated = true;
        }
        return GetDisplayGraph();
    }
}
    
std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplayNcurses()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;
    display.push_back(std::make_pair("*clear", std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
    display.push_back(std::make_pair("Score:" + std::to_string(score), std::make_pair(std::make_pair(4, 57), std::make_pair(6, 6))));
    updateGame(display);
    return display;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameSnake::GetDisplayGraph()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;
    display.push_back(std::make_pair("Score: " + std::to_string(score), std::make_pair(std::make_pair(100, 20), std::make_pair(200, 50))));
    updateGameGraph(display);
    return display;
}

void arcade::GameSnake::setKey(enum arcade::KeyBind key)
{
    switch (key) {
        case arcade::KeyBind::UP_KEY:
            if (direction != Direction::DOWN)
                direction = Direction::UP;
            break;
        case arcade::KeyBind::DOWN_KEY:
            if (direction != Direction::UP)
                direction = Direction::DOWN;
            break;
        case arcade::KeyBind::LEFT_KEY:
            if (direction != Direction::RIGHT)
                direction = Direction::LEFT;
            break;
        case arcade::KeyBind::RIGHT_KEY:
            if (direction != Direction::LEFT)
                direction = Direction::RIGHT;
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
    if (lib == arcade::TGraphics::NCURSES)
        return "";
    return "assets/Snake/snake.wav";
}

std::string arcade::GameSnake::getActGame()
{
    if (gameOver == true)
        return "Game Over";
    return "Game Snake";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GameSnake();
}
