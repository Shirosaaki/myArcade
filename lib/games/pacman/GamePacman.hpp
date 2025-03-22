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
            virtual std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplay(enum arcade::TGraphics lib) override;
            virtual void setKey(enum arcade::KeyBind key) override;
            virtual int getScore() override;
            virtual std::string getSound(enum arcade::TGraphics lib) override;
    };
}

#endif /* !GAME_PACMAN_HPP_ */
