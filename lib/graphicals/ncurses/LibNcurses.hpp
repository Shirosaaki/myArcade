/*
** EPITECH PROJECT, 2025
** Lib Ncurses
** File description:
** no
*/

#ifndef LIBNCURSES_HPP_
    #define LIBNCURSES_HPP_
    #include "../IGraphics.hpp"
    #include <ncurses.h>
    #define COLOR_BRIGHT_MAGENTA 9
    #define COLOR_ORANGE 16
    #include <iostream>
    
namespace arcade {
    class LibNcurses : public IGraphics {
        public:
            LibNcurses();
            ~LibNcurses();
            void Init() override;
            arcade::KeyBind getKey() override;
            void Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities) override;
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;
        protected:
        private:
    };
}

#endif /* !LIBNCURSES_HPP_ */
