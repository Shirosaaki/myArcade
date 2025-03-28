#include "GameSnake.hpp"
#include <ncurses.h>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

arcade::GameSnake::GameSnake() : score(0), direction(1), gameOver(false) {
    srand(time(0));

    snake.push_back(std::make_pair(10, 9));
    snake.push_back(std::make_pair(10, 8));
    snake.push_back(std::make_pair(10, 7));

    generateFruit();
}

arcade::GameSnake::~GameSnake() {
}

void arcade::GameSnake::createBox() {
    boxGame = newwin(35, 70, 7, 55);
    box(boxGame, 0, 0);
    getmaxyx(boxGame, yMaxBox, xMaxBox);
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

void arcade::GameSnake::updateGame(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities) {
    entities["*clear"] = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
    for (size_t i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    switch (direction) {
        case 0: // Haut
            snake[0].first--;
            break;
        case 1: // Droite
            snake[0].second++;
            break;
        case 2: // Bas
            snake[0].first++;
            break;
        case 3: // Gauche
            snake[0].second--;
            break;
    }

    if (snake[0] == fruit) {
        snake.push_back(snake.back());
        score += 10;
        generateFruit();
    }
}

bool arcade::GameSnake::checkCollisions() {
    auto head = snake.front();
     if (head.first <= 1 || head.first >= 34 || head.second <= 1 || head.second >= 69) {
        mvprintw(1, 75, "Collision ");
        return true;
    }
    return false;
}

bool arcade::GameSnake::isGameOver() {
    gameOver = checkCollisions();
    return gameOver;
}

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GameSnake::GetDisplay(enum arcade::TGraphics lib) {
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> body_snake;
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;

    if (lib == arcade::TGraphics::NCURSES) {
        body_snake["$"] = std::make_pair(std::make_pair(snake[0].first, snake[0].second), std::make_pair(2, 2));

        int i = 0;
        for (const auto& segment : snake) {
            if (i == 0) {
                i++;
                continue;
            }
            auto key = std::to_string(i);
            body_snake["O*" + key] = std::make_pair(std::make_pair(segment.first, segment.second), std::make_pair(2,2 ));
            i++;
        }
        updateGame(body_snake);
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                setKey(arcade::KeyBind::UP_KEY);
                break;
            case KEY_DOWN:
                setKey(arcade::KeyBind::DOWN_KEY);
                break;
            case KEY_LEFT:
                setKey(arcade::KeyBind::LEFT_KEY);
                break;
            case KEY_RIGHT:
                setKey(arcade::KeyBind::RIGHT_KEY);
                break;
            }
        usleep(100000);
    } else {
        entities["assets/snake.png"] = std::make_pair(std::make_pair(0, 0), std::make_pair(50, 50));
    }
    return body_snake;
}

void arcade::GameSnake::setKey(enum arcade::KeyBind key) {
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

int arcade::GameSnake::getScore() {
    return score;
}

std::string arcade::GameSnake::getSound(enum arcade::TGraphics lib) {
    (void)lib;
    return "";
}

extern "C" arcade::IGames *entryPoint() {
    return new arcade::GameSnake();
}
