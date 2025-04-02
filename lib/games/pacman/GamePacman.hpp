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

namespace arcade {
    class GamePacman : public IGames {
        public:
            GamePacman();
            ~GamePacman();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplay(enum arcade::TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame() override { return "lib/arcade_pacman.so"; }
    };
}

#endif /* !GAME_PACMAN_HPP_ */
