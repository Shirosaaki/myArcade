/*
** EPITECH PROJECT, 2025
** Lib Ncurses
** File description:
** no
*/
#include "LibNcurses.hpp"

arcade::LibNcurses::LibNcurses()
{
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
    case 113:
        return KeyBind::Q_KEY;
    case 115:
        return KeyBind::S_KEY;
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

void arcade::LibNcurses::Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    for (const auto &entity : entities) {
        attron(COLOR_PAIR(entity.second.second.first));
        mvprintw(entity.second.first.first, entity.second.first.second, "%s", entity.first.c_str());
        attroff(COLOR_PAIR(entity.second.second.first));
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
    std::cout << "initialize ncurses" << std::endl;
    return new arcade::LibNcurses();
}