/*
** EPITECH PROJECT, 2025
** Board
** File description:
** Board
*/

#include "Board.hpp"

arcade::Board::Board(int height, int width)
{
    _height = height;
    _width = width;
}

void arcade::Board::init()
{
    _xMax = (getmaxx(stdscr) - _width) / 2;
    _yMax = (getmaxy(stdscr) - _height) / 2;
    _boxGame = newwin(_height, _width, _yMax, _xMax);
    clear();
    refresh();
}

void arcade::Board::clear()
{
    //wclear(_boxGame);
    addBorder();
}

void arcade::Board::addBorder()
{
    box(_boxGame, 0, 0);
}

void arcade::Board::refresh()
{
    wrefresh(_boxGame);
}

void arcade::Board::addAt(int x, int y, chtype ch)
{
    mvwaddch(_boxGame, x, y, ch);
}

chtype arcade::Board::getInput()
{
    return wgetch(_boxGame);
}