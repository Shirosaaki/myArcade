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
            void addBorder();
            void clear();
            void refresh();
            void init();
            void addAt(int x, int y, chtype ch);  // Add a character at position 
            chtype getInput();
    };
}


#endif

