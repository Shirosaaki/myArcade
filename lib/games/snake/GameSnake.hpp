/*
** EPITECH PROJECT, 2025
** GameSnake
** File description:
** GameSnake
*/
#ifndef GAME_SNAKE_HPP_
    #define GAME_SNAKE_HPP_
    #include "../IGames.hpp"
    #include <map>

namespace arcade {
    class GameSnake : public IGames {
        public:
            GameSnake();
            ~GameSnake();
            virtual std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> GetDisplay(enum arcade::TGraphics lib) override;
            virtual void setKey(enum arcade::KeyBind key) override;
            virtual int getScore() override;
            virtual std::string getSound(enum arcade::TGraphics lib) override;
    };
}

#endif /* !GAME_SNAKE_HPP_ */
