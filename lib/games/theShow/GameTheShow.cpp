/*
** EPITECH PROJECT, 2025
** GameTheShow
** File description:
** GameTheShow
*/
#include "GameTheShow.hpp"

arcade::GameTheShow::GameTheShow()
{
    this->pos = std::make_pair(630, 360);
    this->ennemiPos = std::make_pair(800, 300);
}

arcade::GameTheShow::~GameTheShow()
{
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::displayFirstCinematic()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeMove);

    if (nbFrames == 131) {
        isTheFirstTime = false;
        return entities;
    }
    if (elapsed.count() > 175) {
        if (nbFrames == 0)
            nbFrames++;
        entities.emplace_back("assets/theShow/movies/intro/intro_frame_" + std::to_string(nbFrames) + ".jpg", std::make_pair(std::make_pair(0, 0), std::make_pair(1080, 720)));
        timeMove = now;
        nbFrames++;
        
    } else
        entities.emplace_back("assets/theShow/movies/intro/intro_frame_" + std::to_string(nbFrames) + ".jpg", std::make_pair(std::make_pair(0, 0), std::make_pair(1080, 720)));
    return entities;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::displaySecondCinematic()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeMove);

    if (nbFrames == 112) {
        _needDisplaySecondCinematic = false;
        return entities;
    }
    if (elapsed.count() > 90) {
        if (nbFrames == 0)
            nbFrames++;
        entities.emplace_back("assets/theShow/movies/sammy/sammy_frame_" + std::to_string(nbFrames) + ".jpg", std::make_pair(std::make_pair(251, 0), std::make_pair(577, 720)));
        timeMove = now;
        nbFrames++;
    } else
        entities.emplace_back("assets/theShow/movies/sammy/sammy_frame_" + std::to_string(nbFrames) + ".jpg", std::make_pair(std::make_pair(251, 0), std::make_pair(577, 720)));
    return entities;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::displayLevel1()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeMove);
    if (elapsed.count() > 400)
        isMoving = false;
    entities.emplace_back("assets/theShow/maison.png", std::make_pair(std::make_pair(0, 0), std::make_pair(1080, 720)));
    if (isMoving == true) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);
        if (elapsed.count() > 200) {
            moveIndex = (moveIndex + 1) % 3;
            lastMoveTime = now;
        }
        if (isRight == true) {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricWalk1.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricWalk2.png", std::make_pair(pos, std::make_pair(105, 150)));
        } else {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricWalk12.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricWalk22.png", std::make_pair(pos, std::make_pair(105, 150)));
        }
    } else if (isRight == true)
        entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
    else
        entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
    return entities;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::displayLevel2()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeMove);
    if (elapsed.count() > 400)
        isMoving = false;
    entities.emplace_back("assets/theShow/ada.png", std::make_pair(std::make_pair(0, 0), std::make_pair(1080, 720)));
    if (isMoving == true) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);
        if (elapsed.count() > 200) {
            moveIndex = (moveIndex + 1) % 3;
            lastMoveTime = now;
        }
        if (isRight == true) {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricWalk1.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricWalk2.png", std::make_pair(pos, std::make_pair(105, 150)));
        } else {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricWalk12.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricWalk22.png", std::make_pair(pos, std::make_pair(105, 150)));
        }
    } else if (isAttack == true) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);
        if (elapsed.count() > 200) {
            moveIndex = (moveIndex + 1) % 5;
            lastMoveTime = now;
            if (moveIndex == 4) {
                isAttack = false;
                moveIndex = 0;
                ennemiLife--;
                if (ennemiLife == 0) {
                    actualLevel = 1;
                    isMoving = false;
                    isRight = true;
                    pos.first = 630;
                    pos.second = 360;
                    canAttack = true;
                    ennemiLife = 3;
                    life = 3;
                    _needDisplaySecondCinematic = true;
                    nbFrames = 1;
                }
            }
        }
        if (isRight == true) {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricAttack1.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricAttack2.png", std::make_pair(pos, std::make_pair(105, 150)));
            else if (moveIndex == 3)
                entities.emplace_back("assets/theShow/EricAttack3.png", std::make_pair(pos, std::make_pair(105, 150)));
        } else {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricAttack12.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricAttack22.png", std::make_pair(pos, std::make_pair(105, 150)));
            else if (moveIndex == 3)
                entities.emplace_back("assets/theShow/EricAttack32.png", std::make_pair(pos, std::make_pair(105, 150)));
        }
    }  else if (isRight == true)
        entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
    else
        entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
    if (isEnnemiAttack == true) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastEnnemiMoveTime);
        if (elapsed.count() > 200) {
            ennemiMoveIndex = (ennemiMoveIndex + 1) % 5;
            lastEnnemiMoveTime = now;
            if (ennemiMoveIndex == 4) {
                isEnnemiAttack = false;
                ennemiMoveIndex = 0;
                life--;
                if (life == 0) {
                    actualLevel = 3;
                    isMoving = false;
                    isRight = true;
                    pos.first = 250;
                    pos.second = ennemiPos.second;
                    ennemiPos.second -= 50;
                    canAttack = true;
                    ennemiLife = 3;
                    life = 3;
                }
            }
        }
        if (isEnnemiRight == true) {
            if (ennemiMoveIndex == 0)
                entities.emplace_back("assets/theShow/PaulIdle.png", std::make_pair(ennemiPos, std::make_pair(90, 150)));
            else if (ennemiMoveIndex == 1)
                entities.emplace_back("assets/theShow/PaulAttack1.png", std::make_pair(ennemiPos, std::make_pair(100, 150)));
            else if (ennemiMoveIndex == 2)
                entities.emplace_back("assets/theShow/PaulAttack2.png", std::make_pair(ennemiPos, std::make_pair(105, 150)));
            else if (ennemiMoveIndex == 3)
                entities.emplace_back("assets/theShow/PaulAttack3.png", std::make_pair(ennemiPos, std::make_pair(105, 150)));
        } else {
            if (ennemiMoveIndex == 0)
                entities.emplace_back("assets/theShow/PaulIdle2.png", std::make_pair(ennemiPos, std::make_pair(90, 150)));
            else if (ennemiMoveIndex == 1)
                entities.emplace_back("assets/theShow/PaulAttack12.png", std::make_pair(ennemiPos, std::make_pair(100, 150)));
            else if (ennemiMoveIndex == 2)
                entities.emplace_back("assets/theShow/PaulAttack22.png", std::make_pair(ennemiPos, std::make_pair(105, 150)));
            else if (ennemiMoveIndex == 3)
                entities.emplace_back("assets/theShow/PaulAttack32.png", std::make_pair(ennemiPos, std::make_pair(105, 150)));
        }
    } else if (isEnnemiRight == true)
        entities.emplace_back("assets/theShow/PaulIdle.png", std::make_pair(ennemiPos, std::make_pair(90, 150)));
    else
        entities.emplace_back("assets/theShow/PaulIdle2.png", std::make_pair(ennemiPos, std::make_pair(90, 150)));
    return entities;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::displayLevel3()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeMove);
    if (elapsed.count() > 400)
        isMoving = false;
    entities.emplace_back("assets/theShow/phoenix.png", std::make_pair(std::make_pair(0, 0), std::make_pair(1080, 720)));
    if (isMoving == true) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);
        if (elapsed.count() > 200) {
            moveIndex = (moveIndex + 1) % 3;
            lastMoveTime = now;
        }
        if (isRight == true) {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricWalk1.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricWalk2.png", std::make_pair(pos, std::make_pair(105, 150)));
        } else {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricWalk12.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricWalk22.png", std::make_pair(pos, std::make_pair(105, 150)));
        }
    } else if (isAttack) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime);
        if (elapsed.count() > 200) {
            moveIndex = (moveIndex + 1) % 5;
            lastMoveTime = now;
            if (moveIndex == 4) {
                isAttack = false;
                moveIndex = 0;
                ennemiLife--;
                if (ennemiLife == 0) {
                    actualLevel = 4;
                    isMoving = false;
                    isRight = true;
                    pos.first = 630;
                    pos.second = 360;
                    canAttack = true;
                    ennemiLife = 3;
                    life = 3;
                }
            }
        }
        if (isRight) {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricAttack1.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricAttack2.png", std::make_pair(pos, std::make_pair(105, 150)));
            else if (moveIndex == 3)
                entities.emplace_back("assets/theShow/EricAttack3.png", std::make_pair(pos, std::make_pair(105, 150)));
        } else {
            if (moveIndex == 0)
                entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
            else if (moveIndex == 1)
                entities.emplace_back("assets/theShow/EricAttack12.png", std::make_pair(pos, std::make_pair(100, 150)));
            else if (moveIndex == 2)
                entities.emplace_back("assets/theShow/EricAttack22.png", std::make_pair(pos, std::make_pair(105, 150)));
            else if (moveIndex == 3)
                entities.emplace_back("assets/theShow/EricAttack32.png", std::make_pair(pos, std::make_pair(105, 150)));
        }
    } else if (isRight == true)
        entities.emplace_back("assets/theShow/EricIdle.png", std::make_pair(pos, std::make_pair(90, 150)));
    else
        entities.emplace_back("assets/theShow/EricIdle2.png", std::make_pair(pos, std::make_pair(90, 150)));
    if (isEnnemiAttack == true) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastEnnemiMoveTime);
        if (elapsed.count() > 200) {
            ennemiMoveIndex = (ennemiMoveIndex + 1) % 4;
            lastEnnemiMoveTime = now;
            if (ennemiMoveIndex == 3) {
                isEnnemiAttack = false;
                ennemiMoveIndex = 0;
                life--;
                if (life == 0) {
                    actualLevel = 3;
                    isMoving = false;
                    isRight = true;
                    pos.first = 250;
                    pos.second = ennemiPos.second + 50;
                    ennemiLife = 3;
                    life = 3;
                }
            }
        }
        if (isEnnemiRight == true) {
            if (ennemiMoveIndex == 0)
                entities.emplace_back("assets/theShow/SammyIdle.png", std::make_pair(ennemiPos, std::make_pair(90, 200)));
            else if (ennemiMoveIndex == 1)
                entities.emplace_back("assets/theShow/SammyAttack1.png", std::make_pair(ennemiPos, std::make_pair(100, 200)));
            else if (ennemiMoveIndex == 2)
                entities.emplace_back("assets/theShow/SammyAttack2.png", std::make_pair(ennemiPos, std::make_pair(105, 200)));
        } else {
            if (ennemiMoveIndex == 0)
                entities.emplace_back("assets/theShow/SammyIdle2.png", std::make_pair(ennemiPos, std::make_pair(90, 200)));
            else if (ennemiMoveIndex == 1)
                entities.emplace_back("assets/theShow/SammyAttack12.png", std::make_pair(ennemiPos, std::make_pair(100, 200)));
            else if (ennemiMoveIndex == 2)
                entities.emplace_back("assets/theShow/SammyAttack22.png", std::make_pair(ennemiPos, std::make_pair(105, 200)));
        }
    } else if (isEnnemiRight == true)
        entities.emplace_back("assets/theShow/SammyIdle.png", std::make_pair(ennemiPos, std::make_pair(90, 200)));
    else
        entities.emplace_back("assets/theShow/SammyIdle2.png", std::make_pair(ennemiPos, std::make_pair(90, 200)));
    return entities;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::displayLevel4()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    return entities;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::displayLevel5()
{
    std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> entities;
    return entities;
}

void arcade::GameTheShow::changeLevel()
{
    return;
}

std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> arcade::GameTheShow::GetDisplay(enum TGraphics lib)
{
    if (lib == TGraphics::NCURSES) {
        std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> entity;
        entity.first = "THE_SHOW";
        entity.second.first = std::make_pair(0, 0);
        entity.second.second = std::make_pair(6, 6);
        return {entity};
    } if (isTheFirstTime == true)
        return displayFirstCinematic();
    if (_needDisplaySecondCinematic == true)
        return displaySecondCinematic();
    if (actualLevel == 1)
        return displayLevel1();
    if (actualLevel == 2)
        return displayLevel2();
    if (actualLevel == 3)
        return displayLevel3();
    if (actualLevel == 4)
        return displayLevel4();
    else
        return displayLevel5();
}

void arcade::GameTheShow::setKey(enum KeyBind key)
{
    if (key == KeyBind::LEFT_KEY && canMove && pos.first > 0) {
        pos.first -= 10;
        isRight = false;
        isMoving = true;
        isAttack = false;
        timeMove = std::chrono::steady_clock::now();
    } else if (key == KeyBind::RIGHT_KEY && canMove && pos.first < 990) {
        pos.first += 10;
        isRight = true;
        isMoving = true;
        isAttack = false;
        timeMove = std::chrono::steady_clock::now();
    } else if (key == KeyBind::ENTER && canAttack == true) {
        isAttack = true;
        isMoving = false;
    }
    if (pos.first == 0 && actualLevel == 1) {
        actualLevel = 2;
        isMoving = false;
        isRight = true;
        pos.first = 250;
        pos.second = 300;
        canAttack = true;
    }
    if (pos.first > ennemiPos.first + 20)
        isEnnemiRight = true;
    else if (pos.first < ennemiPos.first - 20)
        isEnnemiRight = false;
    if (pos.first > ennemiPos.first - 50 && pos.first < ennemiPos.first + 50 && isEnnemiAttack == false)
        isEnnemiAttack = true;
}

int arcade::GameTheShow::getScore()
{
    return 1410065407;
}

std::string arcade::GameTheShow::getSound(enum TGraphics lib)
{
    if (lib != TGraphics::NCURSES && isTheFirstTime == true)
        return "assets/theShow/intro.wav";
    if (lib != TGraphics::NCURSES && _needDisplaySecondCinematic == true)
        return "assets/theShow/sammy.wav";
    else
        return "assets/menu/TheShost.wav";
}

std::string arcade::GameTheShow::getActGame()
{
    return "theShow";
}

extern "C" arcade::IGames *entryPoint()
{
    return new arcade::GameTheShow();
}
