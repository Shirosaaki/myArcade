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
    #include <map>
    #include <filesystem>

namespace arcade {
    class GameMenu : public IGames {
        public:
            GameMenu();
            ~GameMenu();
            std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> getDisplay(enum TGraphics lib) override;
            void setKey(enum arcade::KeyBind key) override;
            int getScore() override;
            std::string getSound(enum arcade::TGraphics lib) override;
            std::string getActGame();
            void resetGame() override { return; }
            
        protected:
            std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> loadGamesLibs(const std::string &path);
            arcade::TGames getGame(const std::string& lib);
            arcade::IGames *getGameLib(const std::string& lib);

        private:
            int cursor = 1;
            int nbGames = 2;
            std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> gameMap;
            std::string actGame;
    };
}

#endif /* !GAME_MENU_HPP_ */
