/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/
#ifndef GAME_SNAKE_HPP_
    #define GAME_SNAKE_HPP_

#include "../IGames.hpp"
#include <ncurses.h>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

namespace arcade {
    class GameSnake : public IGames {
        private:
            std::vector<std::pair<int, int>> snake;
            std::pair<int, int> fruit;
            int score;
            int direction;

        public:
            GameSnake();
            ~GameSnake();
            std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplay(enum arcade::TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame() override { return "lib/arcade_snake.so"; }
            void updateGame();
            void generateFruit();
    };
}

#endif /* !GAME_SNAKE_HPP_ */

