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

void arcade::Board::initBoard()
{
    _xMax = (getmaxx(stdscr) - _width) / 2;
    _yMax = (getmaxy(stdscr) - _height) / 2;
    _boxGame = newwin(_height, _width, _yMax, _xMax);
    box(_boxGame, 0, 0);
    wrefresh(_boxGame);
}