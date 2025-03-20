/*
** EPITECH PROJECT, 2025
** Lib Ncurses
** File description:
** no
*/
#include "LibNcurses.hpp"

arcade::LibNcurses::LibNcurses()
{
    Init();
}

arcade::LibNcurses::~LibNcurses()
{
}

void arcade::LibNcurses::Init()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

arcade::KeyBind arcade::LibNcurses::getKey()
{
    int key = getch();

    switch (key) {
    case 27:
        return KeyBind::ESC;
    case 97:
        return KeyBind::A_KEY;
    case 122:
        return KeyBind::Z_KEY;
    case 32:
        return KeyBind::SPACE;
    case 10:
        return KeyBind::ENTER;
    case 258:
        return KeyBind::DOWN_KEY;
    case 259:
        return KeyBind::UP_KEY;
    case 260:
        return KeyBind::LEFT_KEY;
    case 261:
        return KeyBind::RIGHT_KEY;
    default:
        return KeyBind::NONE;
    }
}

void arcade::LibNcurses::Display(std::map<std::string, std::vector<std::pair<int, int>>> &entities)
{
    for (auto &entity : entities) {
        for (auto &pos : entity.second) {
            attron(COLOR_PAIR(std::stoi(entity.first)));
            mvprintw(pos.second, pos.first, " ");
            attroff(COLOR_PAIR(std::stoi(entity.first)));
        }
    }
    refresh();
}

void arcade::LibNcurses::PlaySound(std::string sound)
{
    (void)sound;
}

void arcade::LibNcurses::Clear()
{
    clear();
}

void arcade::LibNcurses::Nuke()
{
    endwin();
}


extern "C" arcade::IGraphics *entryPoint()
{
    return new arcade::LibNcurses();
}
