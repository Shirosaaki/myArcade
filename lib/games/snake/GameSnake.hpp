/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/
#ifndef GAME_SNAKE_HPP_
    #define GAME_SNAKE_HPP_
    #include "../IGames.hpp"
    #include <map>
    #include <vector>
    #include <ncurses.h>
    #include <ctime>
    #include <cstdlib>
    #include <utility>
    #include "../../graphicals/ncurses/LibNcurses.hpp"

namespace arcade {
    class GameSnake : public IGames {
        private:
            enum Direction {
                UP,
                DOWN,
                LEFT,
                RIGHT
            } direction;
            std::vector<std::pair<int, int>> snake;
            std::pair<int, int> fruit;
            int score;
            LibNcurses ncurses;
        public:
            GameSnake();
            ~GameSnake();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplay(enum arcade::TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame() override { return "lib/arcade_snake.so"; }
            void generateFruit();
            void updateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities);
            void generateMap(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities);
    };
}

#endif /* !GAME_SNAKE_HPP_ */