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
    start_player_pos = player_pos;
    tpl_pos = std::make_pair(14, 1);
    tpr_pos = std::make_pair(14, map[0].size() - 3);
    currentDirection = RIGHT;
    nextDirection = RIGHT;
    red_ghost_pos = std::make_pair(11, map[0].size()/ 2 - 1);
    pink_ghost_pos = std::make_pair(13, map[0].size()/ 2 - 1);
    orange_ghost_pos = std::make_pair(13, map[0].size()/ 2 - 2);
    blue_ghost_pos = std::make_pair(13, map[0].size()/ 2);
    start_red_ghost_pos = red_ghost_pos;
    start_pink_ghost_pos = pink_ghost_pos;
    start_orange_ghost_pos = orange_ghost_pos;
    start_blue_ghost_pos = blue_ghost_pos;
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

void arcade::GamePacman::moveOrangeGhost(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastOrangeGhostMoveTime);

    if (elapsed.count() < 300)
        return;
    lastOrangeGhostMoveTime = now;
    if (!clear){
        entities["*clear"] = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
        clear = true;
    }
    double distance = std::hypot(orange_ghost_pos.first - player_pos.first, orange_ghost_pos.second - player_pos.second);
    std::pair<int, int> nextPos;

    if (distance <= 8) {
        nextPos = findShortestPath(orange_ghost_pos, player_pos);
    } else {
        std::vector<std::pair<int, int>> directions = {
            {0, 1},  // Right
            {0, -1}, // Left
            {1, 0},  // Down
            {-1, 0}  // Up
        };

        std::vector<std::pair<int, int>> validMoves;
        for (const auto &dir : directions) {
            std::pair<int, int> neighbor = {orange_ghost_pos.first + dir.first, orange_ghost_pos.second + dir.second};
            if (neighbor.first >= 0 && neighbor.first < map.size() &&
                neighbor.second >= 0 && neighbor.second < map[neighbor.first].size() &&
                map[neighbor.first][neighbor.second] != '#' && neighbor != tpl_pos && neighbor != tpr_pos) {
                validMoves.push_back(neighbor);
            }
        }

        if (!validMoves.empty()) {
            nextPos = validMoves[rand() % validMoves.size()];
        } else {
            nextPos = orange_ghost_pos;
        }
    }

    if (Fear == true)
        nextPos = findFarthestPath(orange_ghost_pos, player_pos);
    orange_ghost_pos = nextPos;
}

void arcade::GamePacman::moveBlueGhost(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastBlueGhostMoveTime);

    if (elapsed.count() < 300)
        return;
    lastBlueGhostMoveTime = now;
    if (!clear){
        entities["*clear"] = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
        clear = true;
    }
    std::pair<int, int> target = player_pos;
    switch (currentDirection) {
        case UP:
            target.first -= 2;
            break;
        case DOWN:
            target.first += 2;
            break;
        case LEFT:
            target.second -= 2;
            break;
        case RIGHT:
            target.second += 2;
            break;
        default:
            break;
    }
    if (target.first < 0) target.first = 0;
    if (target.first >= map.size()) target.first = map.size() - 1;
    if (target.second < 0) target.second = 0;
    if (target.second >= map[0].size()) target.second = map[0].size() - 1;

    std::pair<int, int> blueTarget = {
        target.first + (target.first - red_ghost_pos.first),
        target.second + (target.second - red_ghost_pos.second)
    };

    if (blueTarget.first < 0) blueTarget.first = 0;
    if (blueTarget.first >= map.size()) blueTarget.first = map.size() - 1;
    if (blueTarget.second < 0) blueTarget.second = 0;
    if (blueTarget.second >= map[0].size()) blueTarget.second = map[0].size() - 1;

    if (map[blueTarget.first][blueTarget.second] == '#' || blueTarget == tpl_pos || blueTarget == tpr_pos)
        blueTarget = target;
    std::pair<int, int> nextPos = findShortestPath(blue_ghost_pos, blueTarget);
    if (Fear == true) {
        nextPos = findFarthestPath(blue_ghost_pos, player_pos);
    }
    blue_ghost_pos = nextPos;
}

void arcade::GamePacman::movePinkGhost(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPinkGhostMoveTime);

    if (elapsed.count() < 300)
        return;
    lastPinkGhostMoveTime = now;
    if (!clear){
        entities["*clear"] = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
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

void arcade::GamePacman::moveRedGhost(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRedGhostMoveTime);
    std::pair<int, int> nextPos = findShortestPath(red_ghost_pos, player_pos);

    if (elapsed.count() < 300)
        return;
    lastRedGhostMoveTime = now;
    if (!clear){
        entities["*clear"] = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
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

    if (elapsed.count() < 200)
        return;
    ghost_timer = now;
    if (ghost_pos == start_pos) {
        ghost_dead = false;
        return;
    }
    std::pair<int, int> nextPos = findShortestPath(ghost_pos, start_pos);
    ghost_pos = nextPos;
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

    UpdateGame(entities);
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::string tmp = "";
            if (cell == '#') {
                tmp += cell;
                tmp += "*";
                tmp += std::to_string(nb);
                nb++;
                entities[tmp] = std::make_pair(std::make_pair(y, x), std::make_pair(11, 11));
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
    if (red_ghost_dead) {
        entities["8"] = std::make_pair(red_ghost_pos, std::make_pair(7, 7));
    }
    if (!red_ghost_dead) {
        if (!Fear) 
            entities["R"] = std::make_pair(red_ghost_pos, std::make_pair(12, 12));
        else
            entities["R"] = std::make_pair(red_ghost_pos, std::make_pair(13, 13));
    }
    if (pink_ghost_dead) {
        entities["8"] = std::make_pair(pink_ghost_pos, std::make_pair(7, 7));
    } else {
        if (!Fear)
            entities["P"] = std::make_pair(pink_ghost_pos, std::make_pair(14, 14));
        else
            entities["P"] = std::make_pair(pink_ghost_pos, std::make_pair(13, 13));
    }
    if (orange_ghost_dead) {
        entities["8"] = std::make_pair(orange_ghost_pos, std::make_pair(7, 7));
    } else {
        if (!Fear)
            entities["O"] = std::make_pair(orange_ghost_pos, std::make_pair(16, 16));
        else
            entities["O"] = std::make_pair(orange_ghost_pos, std::make_pair(13, 13));
    }
    if (blue_ghost_dead) {
        entities["8"] = std::make_pair(blue_ghost_pos, std::make_pair(7, 7));
    } else {
        if (!Fear)
            entities["B"] = std::make_pair(blue_ghost_pos, std::make_pair(15, 15));
        else
            entities["B"] = std::make_pair(blue_ghost_pos, std::make_pair(13, 13));
    }
    if (!Fear) {
        entities["C"] = std::make_pair(player_pos, std::make_pair(10, 10));
    } else {
        entities["C"] = std::make_pair(player_pos, std::make_pair(8, 8));
    }
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
    if (!clear){
        entities["*clear"] = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
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

void arcade::GamePacman::checkCollision(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
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

void arcade::GamePacman::UpdateGame(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
{
    movePlayer(entities);
    moveDeadGhost(red_ghost_pos, start_red_ghost_pos, red_ghost_dead, red_ghost_dead_timer);
    moveDeadGhost(blue_ghost_pos, start_blue_ghost_pos, blue_ghost_dead, blue_ghost_dead_timer);
    moveDeadGhost(orange_ghost_pos, start_orange_ghost_pos, orange_ghost_dead, orange_ghost_dead_timer);
    moveDeadGhost(pink_ghost_pos, start_pink_ghost_pos, pink_ghost_dead, pink_ghost_dead_timer);

    if (!red_ghost_dead) moveRedGhost(entities);
    if (!blue_ghost_dead) moveBlueGhost(entities);
    if (!orange_ghost_dead) moveOrangeGhost(entities);
    if (!pink_ghost_dead) movePinkGhost(entities);
    checkCollision(entities);
    clear = false;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastFearTime);

    if (elapsed.count() >= 10)
        Fear = false;
}