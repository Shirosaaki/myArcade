/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/
#include "GameCore.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2)
            throw Error("Invalid number of arguments");
        GameCore core;
        if (core.getLib(av[1]) == arcade::TGraphics::NONE)
            throw Error("Invalid graphical library");
        core.loadGraphicalsLibs("lib", av[1]);
        core.loadGamesLibs("lib");
        core.setCurrentGraphical(av[1]);
        core.setCurrentGame("lib/arcade_menu.so");
        core.setTypeCurrentGame(arcade::TGames::MENU);
        std::cout << "Type the name of the player: ";
        std::string playerName;
        std::getline(std::cin, playerName);
        if (playerName.empty())
            throw Error("Invalid player name");
        core.setCurrentPlayerName(playerName);
        core.setTypeCurrentGraphical(core.getLib(av[1]));
        core.getCurrentGraphical()->Init();
        core.run();
    } catch (const Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
