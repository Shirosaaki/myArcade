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

void arcade::GameSnake::updateGame() {
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
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;


    if (lib == arcade::TGraphics::NCURSES) {  // Ajouter une condition si on appuie sur restart
        while (!isGameOver()) {
            createBox();
            updateGame();

            checkCollisions();

            mvprintw(2, 75, "Dimensions : %d x %d", xMaxBox, yMaxBox);
            mvprintw(4, 75, "WELCOME TO SNAKE !");
            for (const auto& segment : snake) {
                mvwprintw(boxGame, segment.first, segment.second, "O");
            }
            mvwprintw(boxGame ,snake[0].first, snake[0].second, "$");
            mvwprintw(boxGame ,fruit.first, fruit.second, "A");
            mvprintw(6, 55, "SCORE: %d", score);
            wrefresh(boxGame);

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
        }
        erase();
        mvprintw(12, 75, "GAME OVER ! Your score is : %d", score);
        clearok(boxGame, TRUE);
    } else {
        entities["assets/snake.png"] = std::make_pair(std::make_pair(0, 0), std::make_pair(50, 50));
    }
    return entities;
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
