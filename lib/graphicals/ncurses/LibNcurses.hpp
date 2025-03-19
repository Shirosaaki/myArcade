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
    
namespace arcade {
    class LibNcurses : public IGraphics {
        public:
            LibNcurses();
            ~LibNcurses();
            void Init() override;
            KeyBind getKey() override;
            void Display(std::map<std::string, std::vector<std::pair<int, int>>> &entities) override;
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;
        protected:
        private:
    };
}

#endif /* !LIBNCURSES_HPP_ */
