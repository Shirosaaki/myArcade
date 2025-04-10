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
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> getDisplay(enum TGraphics lib);
            void setKey(enum KeyBind key);
            int getScore();
            std::string getSound(enum TGraphics lib);
            std::string getActGame();
            void resetGame() override { return; }

        protected:
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> displayFirstCinematic();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> displaySecondCinematic();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> displayLevel1();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> displayLevel2();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> displayLevel3();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> displayLevel4();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> displayLevel5();
            void changeLevel();
        
        private:
            std::string actGame;
            bool canMove = true;
            bool isRight = true;
            bool isMoving = false;
            std::pair<int, int> pos;
            int moveIndex = 0;
            bool isTheFirstTime = true;
            bool canAttack = false;
            bool isAttack = false;
            std::chrono::time_point<std::chrono::steady_clock> lastMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> timeMove = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> lastEnnemiMoveTime = std::chrono::steady_clock::now();
            int nbFrames = 0;
            int actualLevel = 1;
            int life = 3;
            int ennemiLife = 3;
            bool isEnnemiRight = false;
            bool isEnnemiAttack = false;
            std::pair<int, int> ennemiPos;
            int ennemiMoveIndex = 0;
            bool _needDisplaySecondCinematic = false;
    };
}

#endif /* !GAME_THE_SHOW_HPP_ */
