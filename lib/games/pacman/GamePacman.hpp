/*
** EPITECH PROJECT, 2025
** GamePacman
** File description:
** GamePacman
*/
#ifndef GAME_PACMAN_HPP_
    #define GAME_PACMAN_HPP_
    #include "../IGames.hpp"
    #include <vector>
    #include <chrono>
    #include <algorithm>
    #include <cmath>
    #include <queue>
    #include <unordered_map>
    #include <functional> // for std::hash

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
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplay(enum arcade::TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame() override {
                if (gameOver) {
                    return "Game Over";
                }
                return "Game Running";
            }
            void resetGame() override;

        protected:
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplayNcurses();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplayGraph();
            void movePlayer(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities);
            void moveRedGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities);
            void movePinkGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities);
            void moveOrangeGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities);
            void moveBlueGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities);
            void checkCollision();
            void winGame();
            bool checkWin();
            void moveDeadGhost(std::pair<int, int> &ghost_pos, const std::pair<int, int> &start_pos, bool &ghost_dead, std::chrono::steady_clock::time_point &ghost_timer);
            void UpdateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities);
            std::pair<int, int> findShortestPath(std::pair<int, int> start, std::pair<int, int> end);
            std::pair<int, int> findFarthestPath(std::pair<int, int> start, std::pair<int, int> end);

        private:
            int speed_ghost = 300;
            int speed_player = 200;
            std::vector<std::string> map;
            std::vector<std::string> new_map;
            std::pair<int, int> player_pos;
            std::pair<int, int> start_player_pos;
            std::pair<int, int> red_ghost_pos;
            std::pair<int, int> start_red_ghost_pos;
            std::pair<int, int> pink_ghost_pos; 
            std::pair<int, int> start_pink_ghost_pos;
            std::pair<int, int> blue_ghost_pos;
            std::pair<int, int> start_blue_ghost_pos;
            std::pair<int, int> orange_ghost_pos;
            std::pair<int, int> start_orange_ghost_pos;
            bool red_ghost_dead = false;
            bool blue_ghost_dead = false;
            bool orange_ghost_dead = false;
            bool pink_ghost_dead = false;
            std::pair<int, int> tpl_pos;
            std::pair<int, int> tpr_pos;
            Direction currentDirection = NONE;
            Direction nextDirection = NONE;
            bool Fear = false;
            bool gameOver = false;
            int score = 0;
            int lives = 3;
            bool clear = false;
            std::chrono::time_point<std::chrono::steady_clock> lastMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> lastRedGhostMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> lastPinkGhostMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> lastOrangeGhostMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> lastBlueGhostMoveTime = std::chrono::steady_clock::now();
            std::chrono::time_point<std::chrono::steady_clock> lastFearTime = std::chrono::steady_clock::now();
            std::chrono::steady_clock::time_point red_ghost_dead_timer;
            std::chrono::steady_clock::time_point blue_ghost_dead_timer;
            std::chrono::steady_clock::time_point orange_ghost_dead_timer;
            std::chrono::steady_clock::time_point pink_ghost_dead_timer;
            std::chrono::steady_clock::time_point startTime;
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