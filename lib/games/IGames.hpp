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
        SPACE,
        TETRIS,
        THE_SHOW
    };
    
    class IGames {
        public:
            virtual ~IGames() = default;
            virtual std::map<std::string, std::vector<std::pair<int, int>>> GetDisplay(enum TGraphics lib) = 0;
            virtual void setKey(enum KeyBind key) = 0;
            virtual int getScore() = 0;
            virtual std::string getSound(enum TGraphics lib) = 0;

        private:
    };
}

#endif /* !IGAMES_HPP_ */
