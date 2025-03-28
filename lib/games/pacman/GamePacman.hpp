/*
** EPITECH PROJECT, 2025
** GamePacman
** File description:
** GamePacman
*/
#ifndef GAME_PACMAN_HPP_
    #define GAME_PACMAN_HPP_
    #include "../IGames.hpp"
    #include <map>
    #include <chrono>

namespace arcade {
    class GamePacman : public IGames {
        public:
            enum Direction {
                UP,
                DOWN,
                LEFT,
                RIGHT,
                NONE
            };
            GamePacman();
            ~GamePacman();
            std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplay(enum arcade::TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame() override { return "lib/arcade_pacman.so"; }
        protected:
            std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplayNcurses();
            void movePlayer(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities);
            void my_timer();
        private:
            std::vector<std::string> map;
            std::pair<int, int> player_pos;
            std::pair<int, int> tpl_pos;
            std::pair<int, int> tpr_pos;
            Direction currentDirection = NONE;
            Direction nextDirection = NONE;
            int score = 0;
            int lives = 3;
    };
}

#endif /* !GAME_PACMAN_HPP_ */
