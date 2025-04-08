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
    #include <ctime>
    #include <cstdlib>
    #include <utility>

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
            std::vector<std::pair<int, int>> snakeGraph;
            std::pair<int, int> fruit;
            std::pair<int, int> appleGraph;
            std::pair<int, int> wall;
            std::pair<int, int> offset_pos;
            std::pair<int, int> offset_posGraph;
            int score;
            bool gameOver;
            bool initialized;
            bool isGraphic;
            KeyBind key;
        public:
            GameSnake();
            ~GameSnake();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplay(enum arcade::TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame() override;
            void generateFruit();
            void generateFruitGraph();
            void updateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities);
            void generateMap(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities);
            void checkCollision(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities);
            bool isGameOver();
            void initSnake();
            void resetGame() override;
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplayNcurses();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplayGraph();
            void generateMapGraph(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities);
            void updateGameGraph(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>  &entities);


    };
}

#endif /* !GAME_SNAKE_HPP_ */