#ifndef INCLUDED_BOARD_HPP
    #define INCLUDED_BOARD_HPP

#include <iostream>
#include <ncurses.h>

namespace arcade {
    class Board
    {
        private:
            int _height;
            int _width;
            int _xMax;
            int _yMax;
            WINDOW *_boxGame;
        protected:
        public:
            Board(int height, int width);
            ~Board() = default;
            void initBoard();
    };
}


#endif

