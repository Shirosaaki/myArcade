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
    #include <algorithm>
    #include <cmath>
    #include <queue>
    #include <unordered_map>
    #include <functional> // Pour std::hash

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
            void moveRedGhost(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities);
            void checkCollision(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities);
            void UpdateGame(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities);
            std::pair<int, int> findShortestPath(std::pair<int, int> start, std::pair<int, int> end);
        private:
            std::vector<std::string> map;
            std::pair<int, int> player_pos;
            std::pair<int, int> start_player_pos;
            std::pair<int, int> red_ghost_pos;
            std::pair<int, int> start_red_ghost_pos;
            std::pair<int, int> pink_ghost_pos; 
            std::pair<int, int> blue_ghost_pos;
            std::pair<int, int> orange_ghost_pos;
            std::pair<int, int> tpl_pos;
            std::pair<int, int> tpr_pos;
            Direction currentDirection = NONE;
            Direction nextDirection = NONE;
            bool Fear = false;
            bool gameOver = false;
            int score = 0;
            int lives = 3;
            std::chrono::time_point<std::chrono::steady_clock> lastMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> lastRedGhostMoveTime = std::chrono::steady_clock::now();
    };
}

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int> &p) const {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };
}

#endif /* !GAME_PACMAN_HPP_ */
