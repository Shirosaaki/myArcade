/*
** EPITECH PROJECT, 2025
** GamePacman
** File description:
** GamePacman
*/
#include "GamePacman.hpp"

arcade::GamePacman::GamePacman()
{
    map = {
        "############################*1",
        "#............##............#*2",
        "#.####.#####.##.#####.####.#*3",
        "#O####.#####.##.#####.####O#*4",
        "#.####.#####.##.#####.####.#*5",
        "#..........................#*6",
        "#.####.##.########.##.####.#*7",
        "#.####.##.########.##.####.#*8",
        "#......##....##....##......#*9",
        "######.##### ## #####.######*10",
        "######.##### ## #####.######*11",
        "######.##          ##.######*12",
        "######.## ###  ### ##.######*13",
        "######.## #      # ##.######*14",
        "      .   #      #   .      *15",
        "######.## ######## ##.######*16",
        "######.##          ##.######*17",
        "######.## ######## ##.######*18",
        "######.## ######## ##.######*19",
        "#............##............#*20",
        "#.####.#####.##.#####.####.#*21",
        "#.####.#####.##.#####.####.#*22",
        "#O..##................##..O#*23",
        "###.##.##.########.##.##.###*24",
        "###.##.##.########.##.##.###*25",
        "#......##....##....##......#*26",
        "#.##########.##.##########.#*27",
        "#.##########.##.##########.#*28",
        "#..........................#*29",
        "############################*30"
    };
    player_pos = std::make_pair(22, map[0].size()/2 - 1);
    tpl_pos = std::make_pair(14, 1);
    tpr_pos = std::make_pair(14, map[0].size() - 3);
    currentDirection = RIGHT;
    nextDirection = RIGHT;
}

arcade::GamePacman::~GamePacman()
{
}

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GamePacman::GetDisplay
(enum arcade::TGraphics lib)
{
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;

    if (lib == arcade::TGraphics::NCURSES)
        entities = GetDisplayNcurses();
    else
        entities["assets/pacman.png"] = std::make_pair(std::make_pair(0, 0), std::make_pair(50, 50));
    return entities;
}

void arcade::GamePacman::setKey(enum arcade::KeyBind key)
{
    if (key == arcade::KeyBind::UP_KEY) {
        nextDirection = UP;
    } else if (key == arcade::KeyBind::DOWN_KEY) {
        nextDirection = DOWN;
    } else if (key == arcade::KeyBind::LEFT_KEY) {
        nextDirection = LEFT;
    } else if (key == arcade::KeyBind::RIGHT_KEY) {
        nextDirection = RIGHT;
    }
}

int arcade::GamePacman::getScore()
{
    return score;
}

std::string arcade::GamePacman::getSound(enum arcade::TGraphics lib)
{
    (void)lib;
    return "";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GamePacman();
}

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GamePacman::GetDisplayNcurses()
{
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;
    int nb = 0;
    int y = 0;
    int x = 0;

    movePlayer(entities);
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::string tmp = "";
            if (cell == '#') {
                tmp += cell;
                tmp += "*";
                tmp += std::to_string(nb);
                nb++;
                entities[tmp] = std::make_pair(std::make_pair(y, x), std::make_pair(4, 4));
            } else if (cell == '.') {
                tmp += cell;
                tmp += "*";
                tmp += std::to_string(nb);
                nb++;
                entities[tmp] = std::make_pair(std::make_pair(y, x), std::make_pair(7, 7));
            } else if (cell == 'O') {
                tmp += cell;
                tmp += "*";
                tmp += std::to_string(nb);
                nb++;
                entities[tmp] = std::make_pair(std::make_pair(y, x), std::make_pair(9, 9));
            }
            x++;
        }
        x = 0;
        y++;
    }
    entities["P"] = std::make_pair(player_pos, std::make_pair(3, 3));
    std::string my_score = "Score : ";
    my_score += std::to_string(score);
    entities[my_score] = std::make_pair(std::make_pair(9, map[0].size() + 20), std::make_pair(7, 7));
    std::string my_lives = "Lives :";
    for (int i = 0; i < lives; i++)
        my_lives += " P";
    entities[my_lives] = std::make_pair(std::make_pair(2, map[0].size() + 20), std::make_pair(3, 3));
    return entities;
}

void arcade::GamePacman::movePlayer(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
{
    std::pair<int, int> tmp = player_pos;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);

    if (elapsed.count() < 200)
        return;
    lastMoveTime = now;
    entities["*clear"] = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));

    if (nextDirection != NONE) {
        switch (nextDirection) {
            case UP:
                if (map[player_pos.first - 1][player_pos.second] != '#')
                    currentDirection = UP;
                break;
            case DOWN:
                if (map[player_pos.first + 1][player_pos.second] != '#')
                    currentDirection = DOWN;
                break;
            case LEFT:
                if (map[player_pos.first][player_pos.second - 1] != '#')
                    currentDirection = LEFT;
                break;
            case RIGHT:
                if (map[player_pos.first][player_pos.second + 1] != '#')
                    currentDirection = RIGHT;
                break;
            default:
                break;
        }
    }

    switch (currentDirection) {
        case UP:
            if (map[player_pos.first - 1][player_pos.second] != '#') {
                if (map[player_pos.first - 1][player_pos.second] == '.')
                    score += 10;
                if (map[player_pos.first - 1][player_pos.second] == 'O')
                    score += 50;
                player_pos.first--;
                map[tmp.first][tmp.second] = ' ';
            }
            break;
        case DOWN:
            if (map[player_pos.first + 1][player_pos.second] != '#') {
                if (map[player_pos.first + 1][player_pos.second] == '.')
                    score += 10;
                if (map[player_pos.first + 1][player_pos.second] == 'O')
                    score += 50;
                player_pos.first++;
                map[tmp.first][tmp.second] = ' ';
            }
            break;
        case LEFT:
            if (player_pos == tpl_pos){
                player_pos = tpr_pos;
                map[tpl_pos.first][tpl_pos.second] = ' ';
            } else if (map[player_pos.first][player_pos.second - 1] != '#') {
                if (map[player_pos.first][player_pos.second - 1] == '.')
                    score += 10;
                if (map[player_pos.first][player_pos.second - 1] == 'O')
                    score += 50;
                player_pos.second--;
                map[tmp.first][tmp.second] = ' ';
            }
            break;
        case RIGHT:
            if (player_pos == tpr_pos) {
                player_pos = tpl_pos;
                map[tpr_pos.first][tpr_pos.second] = ' ';
            } else if (map[player_pos.first][player_pos.second + 1] != '#') {
                if (map[player_pos.first][player_pos.second + 1] == '.')
                    score += 10;
                if (map[player_pos.first][player_pos.second + 1] == 'O')
                    score += 50;
                player_pos.second++;
                map[tmp.first][tmp.second] = ' ';
            }
            break;
        default:
            break;
    }
}