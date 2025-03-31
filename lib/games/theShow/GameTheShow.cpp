/*
** EPITECH PROJECT, 2025
** GameTheShow
** File description:
** GameTheShow
*/
#include "GameTheShow.hpp"

arcade::GameTheShow::GameTheShow()
{
    this->pos = std::make_pair(0, 360);
}

arcade::GameTheShow::~GameTheShow()
{
}

std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> arcade::GameTheShow::GetDisplay(enum TGraphics lib)
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeMove);
    if (elapsed.count() > 400) {
        isMoving = false;
    }
    std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entities;
    entities["assets/theShow/maison.png"] = std::make_pair(std::make_pair(0, 0), std::make_pair(1080, 720));
    if (isMoving == true) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);
        if (elapsed.count() > 200) {
            moveIndex = (moveIndex + 1) % 3;
            lastMoveTime = now;
        }
        if (isRight == true) {
            if (moveIndex == 0)
                entities["assets/theShow/zEricIdle.png"] = std::make_pair(pos, std::make_pair(90, 150));
            else if (moveIndex == 1)
                entities["assets/theShow/zEricWalk1.png"] = std::make_pair(pos, std::make_pair(100, 150));
            else if (moveIndex == 2)
                entities["assets/theShow/zEricWalk2.png"] = std::make_pair(pos, std::make_pair(105, 150));
        } else {
            if (moveIndex == 0)
                entities["assets/theShow/zEricIdle2.png"] = std::make_pair(pos, std::make_pair(90, 150));
            else if (moveIndex == 1)
                entities["assets/theShow/zEricWalk12.png"] = std::make_pair(pos, std::make_pair(100, 150));
            else if (moveIndex == 2)
                entities["assets/theShow/zEricWalk22.png"] = std::make_pair(pos, std::make_pair(105, 150));
        }
    } else if (isRight == true)
        entities["assets/theShow/zEricIdle.png"] = std::make_pair(pos, std::make_pair(90, 150));
    else
        entities["assets/theShow/zEricIdle2.png"] = std::make_pair(pos, std::make_pair(90, 150));
    return entities;
}

void arcade::GameTheShow::setKey(enum KeyBind key)
{
    if (key == KeyBind::LEFT_KEY && canMove && pos.first > 0) {
        pos.first -= 10;
        isRight = false;
        isMoving = true;
        timeMove = std::chrono::steady_clock::now();
        return;
    }
    if (key == KeyBind::RIGHT_KEY && canMove && pos.first < 990) {
        pos.first += 10;
        isRight = true;
        isMoving = true;
        timeMove = std::chrono::steady_clock::now();
        return;
    }
}

int arcade::GameTheShow::getScore()
{
    return 0;
}

std::string arcade::GameTheShow::getSound(enum TGraphics lib)
{
    (void)lib;
    return "assets/sound.wav";
}

std::string arcade::GameTheShow::getActGame()
{
    return "theShow";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GameTheShow();
}
