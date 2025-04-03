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
    new_map = map;
    player_pos = std::make_pair(22, map[0].size()/2 - 1);
    start_player_pos = player_pos;
    tpl_pos = std::make_pair(14, 1);
    tpr_pos = std::make_pair(14, map[0].size() - 3);
    currentDirection = RIGHT;
    nextDirection = RIGHT;
    red_ghost_pos = std::make_pair(12, map[0].size()/ 2 - 1);
    pink_ghost_pos = std::make_pair(13, map[0].size()/ 2 - 1);
    orange_ghost_pos = std::make_pair(13, map[0].size()/ 2 - 2);
    blue_ghost_pos = std::make_pair(13, map[0].size()/ 2);
    start_red_ghost_pos = red_ghost_pos;
    start_pink_ghost_pos = pink_ghost_pos;
    start_orange_ghost_pos = orange_ghost_pos;
    start_blue_ghost_pos = blue_ghost_pos;
    startTime = std::chrono::steady_clock::now();
}

arcade::GamePacman::~GamePacman()
{
}


std::pair<int, int> arcade::GamePacman::findShortestPath(std::pair<int, int> start, std::pair<int, int> target)
{
    std::vector<std::pair<int, int>> directions = {
        {0, 1},  // Right
        {0, -1}, // Left
        {1, 0},  // Down
        {-1, 0}  // Up
    };
    std::queue<std::pair<int, int>> queue;
    queue.push(start);
    std::unordered_map<std::pair<int, int>, std::pair<int, int>> cameFrom;
    cameFrom[start] = start;
    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();
        if (current == target) {
            break;
        }
        for (const auto &dir : directions) {
            std::pair<int, int> neighbor = {current.first + dir.first, current.second + dir.second};
            if (neighbor.first >= 0 && neighbor.first < map.size() &&
                neighbor.second >= 0 && neighbor.second < map[neighbor.first].size() &&
                map[neighbor.first][neighbor.second] != '#' && neighbor != tpl_pos && neighbor != tpr_pos &&
                cameFrom.find(neighbor) == cameFrom.end()) {
                queue.push(neighbor);
                cameFrom[neighbor] = current;
            }
        }
    }
    if (cameFrom.find(target) == cameFrom.end()) {
        return start;
    }
    std::pair<int, int> step = target;
    while (cameFrom[step] != start) {
        step = cameFrom[step];
    }
    return step;
}

std::pair<int, int> arcade::GamePacman::findFarthestPath(std::pair<int, int> start, std::pair<int, int> target)
{
    std::vector<std::pair<int, int>> directions = {
        {0, 1},  // Right
        {0, -1}, // Left
        {1, 0},  // Down
        {-1, 0}  // Up
    };
    std::pair<int, int> farthestPos = start;
    double maxDistance = -1;

    for (const auto &dir : directions) {
        std::pair<int, int> neighbor = {start.first + dir.first, start.second + dir.second};
        if (neighbor.first >= 0 && neighbor.first < map.size() &&
            neighbor.second >= 0 && neighbor.second < map[neighbor.first].size() &&
            map[neighbor.first][neighbor.second] != '#' && neighbor != tpl_pos && neighbor != tpr_pos) {
            double distance = std::hypot(neighbor.first - target.first, neighbor.second - target.second);
            if (distance > maxDistance) {
                maxDistance = distance;
                farthestPos = neighbor;
            }
        }
    }
    return farthestPos;
}

void arcade::GamePacman::moveOrangeGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastOrangeGhostMoveTime);

    if (elapsed.count() < speed_ghost)
        return;
    lastOrangeGhostMoveTime = now;
    
    if (!clear) {
        entities.push_back(std::make_pair("*clear", 
            std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
        clear = true;
    }

    double distance = std::hypot(orange_ghost_pos.first - player_pos.first, 
                               orange_ghost_pos.second - player_pos.second);
    std::pair<int, int> nextPos;

    if (distance <= 8) {
        nextPos = findShortestPath(orange_ghost_pos, player_pos);
    } else {
        std::vector<std::pair<int, int>> directions = {
            {0, 1},   // Right
            {0, -1},  // Left 
            {1, 0},   // Down
            {-1, 0}   // Up
        };

        std::vector<std::pair<int, int>> validMoves;
        for (const auto& dir : directions) {
            std::pair<int, int> neighbor = {
                orange_ghost_pos.first + dir.first,
                orange_ghost_pos.second + dir.second
            };
            
            if (neighbor.first >= 0 && neighbor.first < map.size() &&
                neighbor.second >= 0 && neighbor.second < map[neighbor.first].size() &&
                map[neighbor.first][neighbor.second] != '#' && 
                neighbor != tpl_pos && neighbor != tpr_pos) {
                validMoves.push_back(neighbor);
            }
        }

        nextPos = validMoves.empty() ? orange_ghost_pos : 
                 validMoves[rand() % validMoves.size()];
    }

    if (Fear) {
        nextPos = findFarthestPath(orange_ghost_pos, player_pos);
    }

    orange_ghost_pos = nextPos;
}

void arcade::GamePacman::moveBlueGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastBlueGhostMoveTime);

    if (elapsed.count() < speed_ghost)
        return;
    lastBlueGhostMoveTime = now;

    if (!clear) {
        entities.push_back(std::make_pair("*clear", 
            std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
        clear = true;
    }

    // Calculate initial target based on player direction
    std::pair<int, int> target = player_pos;
    switch (currentDirection) {
        case UP:    target.first -= 2; break;
        case DOWN:  target.first += 2; break;
        case LEFT:  target.second -= 2; break;
        case RIGHT: target.second += 2; break;
        default: break;
    }

    // Clamp target position to map boundaries
    target.first = std::clamp(target.first, 0, static_cast<int>(map.size()) - 1);
    target.second = std::clamp(target.second, 0, static_cast<int>(map[0].size()) - 1);

    // Calculate blue ghost's special target position
    std::pair<int, int> blueTarget = {
        target.first * 2 - red_ghost_pos.first,
        target.second * 2 - red_ghost_pos.second
    };

    // Clamp blue target position
    blueTarget.first = std::clamp(blueTarget.first, 0, static_cast<int>(map.size()) - 1);
    blueTarget.second = std::clamp(blueTarget.second, 0, static_cast<int>(map[0].size()) - 1);

    // Adjust target if invalid
    if (map[blueTarget.first][blueTarget.second] == '#' || 
        blueTarget == tpl_pos || 
        blueTarget == tpr_pos) {
        blueTarget = target;
    }

    // Determine next position based on fear mode
    std::pair<int, int> nextPos = Fear ? 
        findFarthestPath(blue_ghost_pos, player_pos) :
        findShortestPath(blue_ghost_pos, blueTarget);

    blue_ghost_pos = nextPos;
}

void arcade::GamePacman::movePinkGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPinkGhostMoveTime);

    if (elapsed.count() < speed_ghost)
        return;
    lastPinkGhostMoveTime = now;
    if (!clear) {
        entities.push_back(std::make_pair("*clear", std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
        clear = true;
    }
    std::pair<int, int> target = player_pos;
    switch (currentDirection) {
        case UP:
            target.first -= 4;
            break;
        case DOWN:
            target.first += 4;
            break;
        case LEFT:
            target.second -= 4;
            break;
        case RIGHT:
            target.second += 4;
            break;
        default:
            break;
    }
    if (target.first < 0) target.first = 0;
    if (target.first >= map.size()) target.first = map.size() - 1;
    if (target.second < 0) target.second = 0;
    if (target.second >= map[0].size()) target.second = map[0].size() - 1;

    std::pair<int, int> nextPos = findShortestPath(pink_ghost_pos, target);
    if (Fear == true)
        nextPos = findFarthestPath(pink_ghost_pos, target);
    pink_ghost_pos = nextPos;
}

void arcade::GamePacman::moveRedGhost(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRedGhostMoveTime);
    std::pair<int, int> nextPos = findShortestPath(red_ghost_pos, player_pos);

    if (elapsed.count() < speed_ghost)
        return;
    lastRedGhostMoveTime = now;
    if (!clear) {
        entities.push_back(std::make_pair("*clear", std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
        clear = true;
    }
    if (Fear == true)
        nextPos = findFarthestPath(red_ghost_pos, player_pos);
    red_ghost_pos = nextPos;
}

void arcade::GamePacman::moveDeadGhost(std::pair<int, int> &ghost_pos, const std::pair<int, int> &start_pos, bool &ghost_dead, std::chrono::steady_clock::time_point &ghost_timer)
{
    if (!ghost_dead)
        return;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - ghost_timer);

    if (elapsed.count() < 100)
        return;
    ghost_timer = now;
    if (ghost_pos == start_pos) {
        ghost_dead = false;
        return;
    }
    std::pair<int, int> nextPos = findShortestPath(ghost_pos, start_pos);
    ghost_pos = nextPos;
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

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GamePacman::GetDisplay(enum arcade::TGraphics lib)
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> display;

    if (lib == arcade::TGraphics::NCURSES)
        return GetDisplayNcurses();
    else
        return GetDisplayGraph();
        //display.push_back(std::make_pair("PACMAN", std::make_pair(std::make_pair(390, 330), std::make_pair(280, 50))));
    return display;
}


std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GamePacman::GetDisplayNcurses()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    int nb = 0;
    int y = 0;
    int x = 0;

    UpdateGame(entities);
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::string tmp = "";
            if (cell == '#') {
                tmp += cell;
                tmp += "*";
                tmp += std::to_string(nb);
                nb++;
                entities.push_back(std::make_pair(tmp, std::make_pair(std::make_pair(y, x), std::make_pair(11, 11))));
            } else if (cell == '.') {
                tmp += cell;
                tmp += "*";
                tmp += std::to_string(nb);
                nb++;
                entities.push_back(std::make_pair(tmp, std::make_pair(std::make_pair(y, x), std::make_pair(7, 7))));
            } else if (cell == 'O') {
                tmp += cell;
                tmp += "*";
                tmp += std::to_string(nb);
                nb++;
                entities.push_back(std::make_pair(tmp, std::make_pair(std::make_pair(y, x), std::make_pair(9, 9))));
            }
            x++;
        }
        x = 0;
        y++;
    }
    if (red_ghost_dead) {
        entities.push_back(std::make_pair("8", std::make_pair(red_ghost_pos, std::make_pair(7, 7))));
    }
    if (!red_ghost_dead) {
        if (!Fear) 
            entities.push_back(std::make_pair("R", std::make_pair(red_ghost_pos, std::make_pair(12, 12))));
        else
            entities.push_back(std::make_pair("R", std::make_pair(red_ghost_pos, std::make_pair(13, 13))));
    }
    if (pink_ghost_dead) {
        entities.push_back(std::make_pair("8", std::make_pair(pink_ghost_pos, std::make_pair(7, 7))));
    } else {
        if (!Fear)
            entities.push_back(std::make_pair("P", std::make_pair(pink_ghost_pos, std::make_pair(14, 14))));
        else
            entities.push_back(std::make_pair("P", std::make_pair(pink_ghost_pos, std::make_pair(13, 13))));
    }
    if (orange_ghost_dead) {
        entities.push_back(std::make_pair("8", std::make_pair(orange_ghost_pos, std::make_pair(7, 7))));
    } else {
        if (!Fear)
            entities.push_back(std::make_pair("O", std::make_pair(orange_ghost_pos, std::make_pair(16, 16))));
        else
            entities.push_back(std::make_pair("O", std::make_pair(orange_ghost_pos, std::make_pair(13, 13))));
    }
    if (blue_ghost_dead) {
        entities.push_back(std::make_pair("8", std::make_pair(blue_ghost_pos, std::make_pair(7, 7))));
    } else {
        if (!Fear)
            entities.push_back(std::make_pair("B", std::make_pair(blue_ghost_pos, std::make_pair(15, 15))));
        else
            entities.push_back(std::make_pair("B", std::make_pair(blue_ghost_pos, std::make_pair(13, 13))));
    }
    if (!Fear) {
        entities.push_back(std::make_pair("C", std::make_pair(player_pos, std::make_pair(10, 10))));
    } else {
        entities.push_back(std::make_pair("C", std::make_pair(player_pos, std::make_pair(8, 8))));
    }
    std::string my_score = "Score : ";
    my_score += std::to_string(score);
    entities.push_back(std::make_pair(my_score, std::make_pair(std::make_pair(9, map[0].size() + 20), std::make_pair(7, 7))));
    std::string my_lives = "Lives :";
    for (int i = 0; i < lives; i++)
        my_lives += " P";
    entities.push_back(std::make_pair(my_lives, std::make_pair(std::make_pair(2, map[0].size() + 20), std::make_pair(3, 3))));
    return entities;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GamePacman::GetDisplayGraph()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    int y = 0;
    int x = 0;

    UpdateGame(entities);
    for (const auto& row : map) {
        for (const auto& cell : row) {
            if (cell == '#') {
                entities.push_back(std::make_pair("assets/Pacman/Wall.png", std::make_pair(std::make_pair(x*20, y*20), std::make_pair(20, 20))));
            } else if (cell == '.') {
                entities.push_back(std::make_pair("assets/Pacman/minPacgum.png", std::make_pair(std::make_pair(x*20, y*20), std::make_pair(20, 20))));
            } else if (cell == 'O') {
                entities.push_back(std::make_pair("assets/Pacman/Pacgum.png", std::make_pair(std::make_pair(x*20, y*20), std::make_pair(20, 20))));
            }
            x++;
        }
        x = 0;
        y++;
    }
    
    if (red_ghost_dead) {
        entities.push_back(std::make_pair("assets/Pacman/Dead_Ghost.png", std::make_pair(std::make_pair(red_ghost_pos.second*20, red_ghost_pos.first*20), std::make_pair(20, 20))));
    } else {
        if (!Fear)
            entities.push_back(std::make_pair("assets/Pacman/Red_Ghost.png", std::make_pair(std::make_pair(red_ghost_pos.second*20, red_ghost_pos.first*20), std::make_pair(20, 20))));
        else
            entities.push_back(std::make_pair("assets/Pacman/Fear_Ghost.png", std::make_pair(std::make_pair(red_ghost_pos.second*20, red_ghost_pos.first*20), std::make_pair(20, 20))));
    }
    if (pink_ghost_dead) {
        entities.push_back(std::make_pair("assets/Pacman/Dead_Ghost.png", std::make_pair(std::make_pair(pink_ghost_pos.second*20, pink_ghost_pos.first*20), std::make_pair(20, 20))));
    } else {
        if (!Fear)
            entities.push_back(std::make_pair("assets/Pacman/Pink_Ghost.png", std::make_pair(std::make_pair(pink_ghost_pos.second*20, pink_ghost_pos.first*20), std::make_pair(20, 20))));
        else
            entities.push_back(std::make_pair("assets/Pacman/Fear_Ghost.png", std::make_pair(std::make_pair(pink_ghost_pos.second*20, pink_ghost_pos.first*20), std::make_pair(20, 20))));
    }
    if (orange_ghost_dead) {
        entities.push_back(std::make_pair("assets/Pacman/Dead_Ghost.png", std::make_pair(std::make_pair(orange_ghost_pos.second*20, orange_ghost_pos.first*20), std::make_pair(20, 20))));
    } else {
        if (!Fear)
            entities.push_back(std::make_pair("assets/Pacman/Orange_Ghost.png", std::make_pair(std::make_pair(orange_ghost_pos.second*20, orange_ghost_pos.first*20), std::make_pair(20, 20))));
        else
            entities.push_back(std::make_pair("assets/Pacman/Fear_Ghost.png", std::make_pair(std::make_pair(orange_ghost_pos.second*20, orange_ghost_pos.first*20), std::make_pair(20, 20))));
    }
    if (blue_ghost_dead) {
        entities.push_back(std::make_pair("assets/Pacman/Dead_Ghost.png", std::make_pair(std::make_pair(blue_ghost_pos.second*20, blue_ghost_pos.first*20), std::make_pair(20, 20))));
    } else {
        if (!Fear)
            entities.push_back(std::make_pair("assets/Pacman/Blue_Ghost.png", std::make_pair(std::make_pair(blue_ghost_pos.second*20, blue_ghost_pos.first*20), std::make_pair(20, 20))));
        else
            entities.push_back(std::make_pair("assets/Pacman/Fear_Ghost.png", std::make_pair(std::make_pair(blue_ghost_pos.second*20, blue_ghost_pos.first*20), std::make_pair(20, 20))));
    }
    if (!Fear) {
        if (currentDirection == UP)
            entities.push_back(std::make_pair("assets/Pacman/Pacman_Up.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
        else if (currentDirection == DOWN)
            entities.push_back(std::make_pair("assets/Pacman/Pacman_Down.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
        else if (currentDirection == LEFT)
            entities.push_back(std::make_pair("assets/Pacman/Pacman_Left.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
        else if (currentDirection == RIGHT)
            entities.push_back(std::make_pair("assets/Pacman/Pacman_Right.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
    } else {
        if (currentDirection == UP)
            entities.push_back(std::make_pair("assets/Pacman/Super_Pacman_Up.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
        else if (currentDirection == DOWN)
            entities.push_back(std::make_pair("assets/Pacman/Super_Pacman_Down.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
        else if (currentDirection == LEFT)
            entities.push_back(std::make_pair("assets/Pacman/Super_Pacman_Left.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
        else if (currentDirection == RIGHT)
            entities.push_back(std::make_pair("assets/Pacman/Super_Pacman_Right.png", std::make_pair(std::make_pair(player_pos.second*20, player_pos.first*20), std::make_pair(20, 20))));
    }
    std::string my_score = "Score : ";
    my_score += std::to_string(score);
    entities.push_back(std::make_pair(my_score, std::make_pair(std::make_pair((map[0].size() + 20) + 665, 9*20), std::make_pair(60, 60))));
    for(int i = 1; i <= lives; i++)
        entities.push_back(std::make_pair("assets/Pacman/Pacman_Right.png", std::make_pair(std::make_pair((map[0].size() + 20) + 600 + i*65, 2*20), std::make_pair(60, 60))));
    return entities;

}

void arcade::GamePacman::movePlayer(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities)
{
    std::pair<int, int> tmp = player_pos;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);

    if (elapsed.count() < speed_player)
        return;
    lastMoveTime = now;
    if (!clear) {
        entities.push_back(std::make_pair("*clear", std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0))));
        clear = true;
    }
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
                if (map[player_pos.first - 1][player_pos.second] == 'O') {
                    score += 50;
                    Fear = true;
                    lastFearTime = std::chrono::steady_clock::now();
                }
                player_pos.first--;
                map[tmp.first][tmp.second] = ' ';
            }
            break;
        case DOWN:
            if (map[player_pos.first + 1][player_pos.second] != '#') {
                if (map[player_pos.first + 1][player_pos.second] == '.')
                    score += 10;
                if (map[player_pos.first + 1][player_pos.second] == 'O') {
                    score += 50;
                    Fear = true;
                    lastFearTime = std::chrono::steady_clock::now();
                }
                player_pos.first++;
                map[tmp.first][tmp.second] = ' ';
            }
            break;
        case LEFT:
            if (player_pos == tpl_pos) {
                player_pos = tpr_pos;
                map[tpl_pos.first][tpl_pos.second] = ' ';
            } else if (map[player_pos.first][player_pos.second - 1] != '#') {
                if (map[player_pos.first][player_pos.second - 1] == '.')
                    score += 10;
                if (map[player_pos.first][player_pos.second - 1] == 'O') {
                    score += 50;
                    Fear = true;
                    lastFearTime = std::chrono::steady_clock::now();
                }
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
                if (map[player_pos.first][player_pos.second + 1] == 'O') {
                    score += 50;
                    Fear = true;
                    lastFearTime = std::chrono::steady_clock::now();
                }
                player_pos.second++;
                map[tmp.first][tmp.second] = ' ';
            }
            break;
        default:
            break;
    }
}

void arcade::GamePacman::checkCollision()
{
    if (player_pos == red_ghost_pos) {
        if (Fear == false) {
            lives--;
            player_pos = start_player_pos;
        } else {
            score += 200;
            red_ghost_dead = true;
            red_ghost_dead_timer = std::chrono::steady_clock::now();
        }
    }
    if (player_pos == pink_ghost_pos) {
        if (Fear == false) {
            lives--;
            player_pos = start_player_pos;
        } else {
            score += 200;
            pink_ghost_dead = true;
            pink_ghost_dead_timer = std::chrono::steady_clock::now();
        }
    }
    if (player_pos == orange_ghost_pos) {
        if (Fear == false) {
            lives--;
            player_pos = start_player_pos;
        } else {
            score += 200;
            orange_ghost_dead = true;
            orange_ghost_dead_timer = std::chrono::steady_clock::now();
        }
    }
    if (player_pos == blue_ghost_pos) {
        if (Fear == false) {
            lives--;
            player_pos = start_player_pos;
        } else {
            score += 200;
            blue_ghost_dead = true;
            blue_ghost_dead_timer = std::chrono::steady_clock::now();
        }
    }

    if (lives <= 0)
        gameOver = true;
}

void arcade::GamePacman::UpdateGame(std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& entities)
{

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);

    if (elapsed.count() < 3)
        return;
    movePlayer(entities);
    if (elapsed.count() < 10) {
        checkCollision();
        clear = false;
        return;
    }
    moveDeadGhost(red_ghost_pos, start_red_ghost_pos, red_ghost_dead, red_ghost_dead_timer);
    moveDeadGhost(blue_ghost_pos, start_blue_ghost_pos, blue_ghost_dead, blue_ghost_dead_timer);
    moveDeadGhost(orange_ghost_pos, start_orange_ghost_pos, orange_ghost_dead, orange_ghost_dead_timer);
    moveDeadGhost(pink_ghost_pos, start_pink_ghost_pos, pink_ghost_dead, pink_ghost_dead_timer);
    if (!red_ghost_dead) moveRedGhost(entities);
    if (!blue_ghost_dead) moveBlueGhost(entities);
    if (!orange_ghost_dead) moveOrangeGhost(entities);
    if (!pink_ghost_dead) movePinkGhost(entities);
    checkCollision();
    if (checkWin()) {
        winGame();
        return;
    }
    clear = false;
    auto elapsedFear = std::chrono::duration_cast<std::chrono::seconds>(now - lastFearTime);

    if (elapsedFear.count() >= 10)
        Fear = false;
}

bool arcade::GamePacman::checkWin()
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '.') {
                return false;
            }
            if (map[i][j] == 'O') {
                return false;
            }
        }
    }
    return true;
}

void arcade::GamePacman::winGame()
{
    map = new_map;
    player_pos = start_player_pos;
    red_ghost_pos = start_red_ghost_pos;
    pink_ghost_pos = start_pink_ghost_pos;
    orange_ghost_pos = start_orange_ghost_pos;
    blue_ghost_pos = start_blue_ghost_pos;
    currentDirection = RIGHT;
    nextDirection = RIGHT;
    Fear = false;
    red_ghost_dead = false;
    blue_ghost_dead = false;
    orange_ghost_dead = false;
    pink_ghost_dead = false;
    gameOver = false;
    clear = false;
    speed_ghost *= 0.9;
    speed_player *= 0.95;
    startTime = std::chrono::steady_clock::now();
    lastMoveTime = std::chrono::steady_clock::now();
    lastRedGhostMoveTime = std::chrono::steady_clock::now();
    lastBlueGhostMoveTime = std::chrono::steady_clock::now();
    lastOrangeGhostMoveTime = std::chrono::steady_clock::now();
    lastPinkGhostMoveTime = std::chrono::steady_clock::now();
    lastFearTime = std::chrono::steady_clock::now();
    red_ghost_dead_timer = std::chrono::steady_clock::now();
    blue_ghost_dead_timer = std::chrono::steady_clock::now();
    orange_ghost_dead_timer = std::chrono::steady_clock::now();
    pink_ghost_dead_timer = std::chrono::steady_clock::now();

}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GamePacman();
}
