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
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();

    if (can_change_color()) {
        // Define orange #FF6600
        init_color(COLOR_ORANGE, 1000, 500, 0);
    }
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK); // pacgum
    init_pair(9, COLOR_BRIGHT_MAGENTA, COLOR_BLACK); // superpacgum
    init_pair(10, COLOR_BLACK, COLOR_YELLOW); // pacman
    init_pair(8, COLOR_YELLOW, COLOR_WHITE); // superpacman
    init_pair(11, COLOR_BLACK, COLOR_BLUE); // Wall
    init_pair(12, COLOR_BLACK, COLOR_RED); // Ghost Red
    init_pair(13, COLOR_WHITE, COLOR_GREEN); // Ghost Fear
    init_pair(14, COLOR_BLACK, COLOR_MAGENTA); // Ghost Pink
    init_pair(15, COLOR_BLACK, COLOR_CYAN); // Ghost Blue
    init_pair(16, COLOR_BLACK, COLOR_ORANGE); // Ghost Orange

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
        this->Clear();
        return KeyBind::DOWN_KEY;
    case 259:
        this->Clear();
        return KeyBind::UP_KEY;
    case 260:
        this->Clear();
        return KeyBind::LEFT_KEY;
    case 261:
        this->Clear();
        return KeyBind::RIGHT_KEY;
    default:
        return KeyBind::NONE;
    }
}

void arcade::LibNcurses::Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    for (auto &entity : entities) {
        std::string tmp = entity.first;
        if (entity.first.find("*clear") != std::string::npos) {
            this->Clear();
            continue;
        }
        if (entity.first.find("*") != std::string::npos) {
            tmp = entity.first.substr(0, entity.first.find("*"));
        }
        attron(COLOR_PAIR(entity.second.second.first));
        mvprintw(entity.second.first.first, entity.second.first.second, "%s", tmp.c_str());
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
