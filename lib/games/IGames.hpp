/*
** EPITECH PROJECT, 2025
** IGames.hpp
** File description:
** IGames.hpp
*/
#ifndef IGAMES_HPP_
    #define IGAMES_HPP_
    #include <iostream>
    #include <vector>
    #include <map>
    #include <string>
    #include "../graphicals/IGraphics.hpp"

namespace arcade {

    enum class TGames {
        SNAKE,
        MINESWEEPER,
        NIBBLER,
        PACMAN,
        QIX,
        CENTIPEDE,
        SOLARFOX,
        SOKOBAN,
        SPACE_INVADER,
        TETRIS,
        THE_SHOW,
        MENU,
        NONE
    };
    
    class IGames {
        public:
            virtual ~IGames() = default;
            virtual std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> GetDisplay(enum TGraphics lib) = 0;
            virtual void setKey(enum KeyBind key) = 0;
            virtual int getScore() = 0;
            virtual std::string getSound(enum TGraphics lib) = 0;
            virtual std::string getActGame() = 0;
            virtual void resetGame() = 0;

        private:
    };
}

#endif /* !IGAMES_HPP_ */
