/*
** EPITECH PROJECT, 2025
** game
** File description:
** menu
*/
#ifndef GAME_MENU_HPP_
    #define GAME_MENU_HPP_
    #include <iostream>
    #include "../IGames.hpp"

namespace arcade {
    class GameMenu : public IGames {
        public:
            GameMenu();
            ~GameMenu();
            virtual std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplay(enum arcade::TGraphics lib) override;
            virtual void setKey(enum arcade::KeyBind key) override;
            virtual int getScore() override;
            virtual std::string getSound(enum arcade::TGraphics lib) override;

        protected:
        private:
    };
}

#endif /* !GAME_MENU_HPP_ */
