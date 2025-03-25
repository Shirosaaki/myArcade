/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/
#ifndef GAME_SNAKE_HPP_
    #define GAME_SNAKE_HPP_
    #include "../IGames.hpp"
    #include "Board.hpp"
    #include <map>

namespace arcade {
    class GameSnake : public IGames {
        private:
            enum Direction {
                UP,
                DOWN,
                LEFT,
                RIGHT
            } direction;
            Board board;
        public:
            GameSnake();
            ~GameSnake();
            std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplay(enum arcade::TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame() override { return "lib/arcade_snake.so"; }
            void handleGame();
    };
}

#endif /* !GAME_SNAKE_HPP_ */

