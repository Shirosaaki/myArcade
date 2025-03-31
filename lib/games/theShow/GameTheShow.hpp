/*
** EPITECH PROJECT, 2025
** theShow
** File description:
** theShow
*/
#ifndef GAME_THE_SHOW_HPP_
    #define GAME_THE_SHOW_HPP_
    #include "../IGames.hpp"
    #include <iostream>
    #include <chrono>
    #include <string>

namespace arcade {
    class GameTheShow : public IGames {
        public:
            GameTheShow();
            ~GameTheShow();
            std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplay(enum TGraphics lib);
            void setKey(enum KeyBind key);
            int getScore();
            std::string getSound(enum TGraphics lib);
            std::string getActGame();
        
        private:
            std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;
            std::string actGame;
            bool canMove = true;
            bool isRight = true;
            bool isMoving = false;
            std::pair<int, int> pos;
            int moveIndex = 0;
            std::chrono::time_point<std::chrono::steady_clock> lastMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> timeMove = std::chrono::steady_clock::now();
    };
}

#endif /* !GAME_THE_SHOW_HPP_ */
