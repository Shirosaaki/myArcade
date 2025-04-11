/*
** EPITECH PROJECT, 2025
** GameCore
** File description:
** GameCore
*/
#include "GameCore.hpp"
#include <algorithm>

GameCore::GameCore()
{
}

GameCore::~GameCore()
{
    for (auto &graphLib: _graphicals)
        if (graphLib.second.second != nullptr) {
            delete graphLib.second.second;
            graphLib.second.second = nullptr;
        }
    for (auto &gameLib: _games)
        if (gameLib.second.second != nullptr) {
            delete gameLib.second.second;
            gameLib.second.second = nullptr;
        }
    for (auto &handle : _handles)
        if (handle) {
            dlclose(handle);
            handle = nullptr;
        }
}

void GameCore::loadGraphicalsLibs(const std::string &path, std::string lib)
{
    std::map<std::string, std::pair<arcade::TGraphics, arcade::IGraphics *>> libMap;
    arcade::IGraphics *graphics = getGraphicsLib(lib);
    if (graphics == nullptr)
        return;
    libMap[lib] = std::make_pair(getLib(lib), graphics);

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string path = entry.path();
        if (path.find("lib/arcade_") == std::string::npos || path == lib)
            continue;
        arcade::TGraphics lib = getLib(path);
        if (lib == arcade::TGraphics::NONE)
            continue;
        arcade::IGraphics *graphics = getGraphicsLib(path);
        if (graphics == nullptr)
            continue;
        libMap[path] = std::make_pair(lib, graphics);
    }
    _graphicals = libMap;
}

void GameCore::loadGamesLibs(const std::string &path)
{
    std::map<std::string, std::pair<arcade::TGames, arcade::IGames *>> gameMap;
    arcade::IGames *game = getGameLib("lib/arcade_menu.so");
    if (game == nullptr)
        return;
    gameMap["lib/arcade_menu.so"] = std::make_pair(arcade::TGames::MENU, game);

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string path = entry.path();
        if (path.find("lib/arcade_") == std::string::npos)
            continue;
        arcade::TGames tgame = getGame(path);
        if (tgame == arcade::TGames::NONE)
            continue;
        arcade::IGames *game = getGameLib(path);
        if (game == nullptr)
            continue;
        gameMap[path] = std::make_pair(tgame, game);
    }
    _games = gameMap;
}

arcade::TGraphics GameCore::getLib(const std::string &lib)
{
    static const std::map<std::string, arcade::TGraphics> libMap = {
        {"lib/arcade_ncurses.so", arcade::TGraphics::NCURSES},
        {"lib/arcade_sdl2.so", arcade::TGraphics::SDL},
        {"lib/arcade_ndk++.so", arcade::TGraphics::NDK},
        {"lib/arcade_aalib.so", arcade::TGraphics::AA},
        {"lib/arcade_libcaca.so", arcade::TGraphics::CACA},
        {"lib/arcade_allegro5.so", arcade::TGraphics::ALLEGRO},
        {"lib/arcade_xlib.so", arcade::TGraphics::X},
        {"lib/arcade_gtk+.so", arcade::TGraphics::GTK},
        {"lib/arcade_sfml.so", arcade::TGraphics::SFML},
        {"lib/arcade_irrlicht.so", arcade::TGraphics::IRRLICHT},
        {"lib/arcade_opengl.so", arcade::TGraphics::OPENGL},
        {"lib/arcade_vulkan.so", arcade::TGraphics::VULKAN},
        {"lib/arcade_qt.so", arcade::TGraphics::QT}
    };
    auto it = libMap.find(lib);
    return (it != libMap.end()) ? it->second : arcade::TGraphics::NONE;
}

arcade::TGames GameCore::getGame(const std::string &lib)
{
    static const std::map<std::string, arcade::TGames> gameMap = {
        {"lib/arcade_snake.so", arcade::TGames::SNAKE},
        {"lib/arcade_minesweeper.so", arcade::TGames::MINESWEEPER},
        {"lib/arcade_nibbler.so", arcade::TGames::NIBBLER},
        {"lib/arcade_pacman.so", arcade::TGames::PACMAN},
        {"lib/arcade_qix.so", arcade::TGames::QIX},
        {"lib/arcade_centipede.so", arcade::TGames::CENTIPEDE},
        {"lib/arcade_solarfox.so", arcade::TGames::SOLARFOX},
        {"lib/arcade_sokoban.so", arcade::TGames::SOKOBAN},
        {"lib/arcade_space_invader.so", arcade::TGames::SPACE_INVADER},
        {"lib/arcade_tetris.so", arcade::TGames::TETRIS},
        {"lib/arcade_the_show.so", arcade::TGames::THE_SHOW},
        {"lib/arcade_menu.so", arcade::TGames::MENU}
    };
    auto it = gameMap.find(lib);
    return (it != gameMap.end()) ? it->second : arcade::TGames::NONE;
}

arcade::IGraphics *GameCore::getGraphicsLib(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen failed: " << dlerror() << std::endl;
        return nullptr;
    }
    arcade::IGraphics *(*entryPoint)();
    entryPoint = (arcade::IGraphics *(*)())dlsym(handle, "entryPoint");
    if (!entryPoint) {
        std::cerr << "dlsym failed: " << dlerror() << std::endl;
        return nullptr;
    }
    _handles.push_back(handle);
    return entryPoint();
}

arcade::IGames *GameCore::getGameLib(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen failed: " << dlerror() << std::endl;
        return nullptr;
    }
    arcade::IGames *(*entryPoint)();
    entryPoint = (arcade::IGames *(*)())dlsym(handle, "entryPoint");
    if (!entryPoint) {
        std::cerr << "dlsym failed: " << dlerror() << std::endl;
        return nullptr;
    }
    _handles.push_back(handle);
    return entryPoint();
}

void GameCore::setCurrentGraphical(const std::string &lib)
{
    auto it = _graphicals.find(lib);
    if (it == _graphicals.end())
        throw Error("Invalid graphical library");
    _currentGraphical = it->second.second;
}

void GameCore::setCurrentGame(const std::string &lib)
{
    auto it = _games.find(lib);
    if (it == _games.end())
        throw Error("Invalid game library");
    _currentGame = it->second.second;
}

void GameCore::konamiCode()
{
    if (_konamiCode.size() <= 10)
        return;
    if (std::equal(_konamiCode.begin(), _konamiCode.end(), std::vector<arcade::KeyBind>{arcade::KeyBind::UP_KEY, arcade::KeyBind::UP_KEY,
        arcade::KeyBind::DOWN_KEY, arcade::KeyBind::DOWN_KEY, arcade::KeyBind::LEFT_KEY, arcade::KeyBind::RIGHT_KEY,
        arcade::KeyBind::LEFT_KEY, arcade::KeyBind::RIGHT_KEY, arcade::KeyBind::SPACE, arcade::KeyBind::A_KEY}.begin())) {
        std::cout << "Konami code activated" << std::endl;
        _konamiCode.clear();
    }
}

void GameCore::nextGraphical()
{
    auto it = std::find_if(_graphicals.begin(), _graphicals.end(),
        [this](const auto &pair) {
            return pair.second.second == _currentGraphical;
        });
    if (it != _graphicals.end()) {
        ++it;
        if (it == _graphicals.end())
            it = _graphicals.begin();
        _currentGraphical->Nuke();
        auto tmp = _currentGraphical;
        _currentGraphical = it->second.second;
        if (_currentGraphical == nullptr) {
            _currentGraphical = tmp;
            return;
        }
        _currentGraphical->Init();
        this->setTypeCurrentGraphical(it->second.first);
        _currentGraphical->Clear();
    } else {
        _currentGraphical->Nuke();
        _currentGraphical = _graphicals.begin()->second.second;
        _currentGraphical->Init();
        this->setTypeCurrentGraphical(_graphicals.begin()->second.first);
        _currentGraphical->Clear();
    }
    _currentGraphical->Clear();
}

void GameCore::prevGraphical()
{
    auto it = std::find_if(_graphicals.begin(), _graphicals.end(),
        [this](const auto &pair) {
            return pair.second.second == _currentGraphical;
        });
    if (it != _graphicals.end()) {
        if (it == _graphicals.begin())
            it = _graphicals.end();
        --it;
        _currentGraphical->Nuke();
        _currentGraphical = it->second.second;
        _currentGraphical->Init();
        this->setTypeCurrentGraphical(it->second.first);
        _currentGraphical->Clear();
    } else {
        _currentGraphical->Nuke();
        _currentGraphical = _graphicals.begin()->second.second;
        _currentGraphical->Init();
        this->setTypeCurrentGraphical(_graphicals.begin()->second.first);
        _currentGraphical->Clear();
    }
    _currentGraphical->Clear();
}

void GameCore::nextGame()
{
    auto it = std::find_if(_games.begin(), _games.end(),
        [this](const auto &pair) {
            return pair.second.second == _currentGame;
        });
    if (it != _games.end()) {
        ++it;
        if (it == _games.end())
            it = _games.begin();
        _currentGame = it->second.second;
        this->setTypeCurrentGame(it->second.first);
        this->_currentGraphical->Clear();
    }
}

void GameCore::prevGame()
{
    auto it = std::find_if(_games.begin(), _games.end(),
        [this](const auto &pair) {
            return pair.second.second == _currentGame;
        });
    if (it != _games.end()) {
        if (it == _games.begin())
            it = _games.end();
        --it;
        _currentGame = it->second.second;
        this->setTypeCurrentGame(it->second.first);
        this->_currentGraphical->Clear();
    }
}

void GameCore::saveScore(int score, const std::string &playerName) {
    using GameScores = std::map<std::string, int>;
    std::vector<std::pair<std::string, GameScores>> allGames;
    std::string currentGameName;
    GameScores currentGameScores;
    std::ifstream inputFile("scores.txt");
    if (inputFile) {
        auto trim = [](const std::string& s) {
            auto start = s.find_first_not_of(" \t");
            return (start == std::string::npos) ? "" : s.substr(start, s.find_last_not_of(" \t") - start + 1);
        };
        std::string line;
        while (std::getline(inputFile, line)) {
            std::string trimmed = trim(line);
            if (trimmed.size() > 4 && trimmed.substr(0, 3) == "-- " && trimmed.substr(trimmed.size() - 3) == " --") {
                if (!currentGameName.empty()) {
                    allGames.emplace_back(currentGameName, currentGameScores);
                    currentGameScores.clear();
                }
                currentGameName = trim(trimmed.substr(3, trimmed.size() - 6));
            }
            else if (!currentGameName.empty() && !trimmed.empty()) {
                size_t colon = trimmed.find(':');
                if (colon != std::string::npos) {
                    std::string name = trim(trimmed.substr(0, colon));
                    int val = std::stoi(trim(trimmed.substr(colon + 1)));
                    currentGameScores[name] = val;
                }
            }
        }
        if (!currentGameName.empty())
            allGames.emplace_back(currentGameName, currentGameScores);
    }
    const std::string CURRENT_GAME = tgameToString(typeCurrentGame);
    auto gameIt = std::find_if(allGames.begin(), allGames.end(),
        [&](const auto& game) { return game.first == CURRENT_GAME; });
    if (gameIt != allGames.end()) {
        auto& [gameName, scores] = *gameIt;
        auto it = scores.find(playerName);
        if (it != scores.end()) {
            if (score > it->second)
                it->second = score;
        } else
            scores[playerName] = score;
    } else
        allGames.emplace_back(CURRENT_GAME, GameScores{{playerName, score}});
    std::ofstream outputFile("scores.txt");
    for (size_t i = 0; i < allGames.size(); ++i) {
        const auto& [name, scores] = allGames[i];
        outputFile << "-- " << name << " --\n";
        for (const auto& [player, highScore] : scores)
            outputFile << player << ": " << highScore << "\n";
        if (i < allGames.size() - 1)
            outputFile << "\n";
    }
}

std::string GameCore::tgameToString(arcade::TGames game)
{
    switch (game) {
        case arcade::TGames::MENU:
            return "MENU";
        case arcade::TGames::PACMAN:
            return "PACMAN";
        case arcade::TGames::SNAKE:
            return "SNAKE";
        case arcade::TGames::MINESWEEPER:
            return "MINESWEEPER";
        case arcade::TGames::NIBBLER:
            return "NIBBLER";
        case arcade::TGames::QIX:
            return "QIX";
        case arcade::TGames::CENTIPEDE:
            return "CENTIPEDE";
        case arcade::TGames::SOLARFOX:
            return "SOLARFOX";
        case arcade::TGames::SOKOBAN:
            return "SOKOBAN";
        case arcade::TGames::SPACE_INVADER:
            return "SPACE_INVADER";
        case arcade::TGames::TETRIS:
            return "TETRIS";
        case arcade::TGames::THE_SHOW:
            return "THE_SHOW";
        default:
            return "UNKNOWN";
    }
}

void GameCore::run()
{
    while (1) {
        auto entities = _currentGame->getDisplay(typeCurrentGraphical);
        _currentGraphical->Display(entities);
        _currentGraphical->PlaySound(_currentGame->getSound(typeCurrentGraphical));
        auto key = _currentGraphical->getKey();
        if (key != arcade::KeyBind::NONE && key != arcade::KeyBind::ESC) {
            _konamiCode.push_back(key);
            this->konamiCode();
        }
        if (key == arcade::KeyBind::ESC) {
            if (typeCurrentGame != arcade::TGames::MENU)
                saveScore(_currentGame->getScore(), _currentPlayerName);
            _currentGraphical->Nuke();
            break;
        } else if (key == arcade::KeyBind::Z_KEY)
            this->nextGraphical();
        else if (key == arcade::KeyBind::A_KEY)
            this->prevGraphical();
        else if (key == arcade::KeyBind::S_KEY)
            this->nextGame();
        else if (key == arcade::KeyBind::Q_KEY)
            this->prevGame();
        else
            _currentGame->setKey(key);
        if (key == arcade::KeyBind::ENTER && this->typeCurrentGame == arcade::TGames::MENU) {
            auto currentGameKey = _currentGame->getActGame();
            _currentGame = _games[currentGameKey].second;
            if (_currentGame == nullptr) {
                this->loadGamesLibs("lib/");
                _currentGame = _games[currentGameKey].second;
            }
            this->setTypeCurrentGame(_games[currentGameKey].first);
            this->_currentGame->resetGame();
            _currentGraphical->Clear();
        }
        if (_currentGame->getActGame() == "Game Over") {
            _currentGraphical->Clear();
            saveScore(_currentGame->getScore(), _currentPlayerName);
            _currentGame = _games["lib/arcade_menu.so"].second;
            if (_currentGame == nullptr) {
                this->loadGamesLibs("lib/");
                _currentGame = _games["lib/arcade_menu.so"].second;
            }
            this->setTypeCurrentGame(arcade::TGames::MENU);
            continue;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const arcade::TGames &game)
{
    if (game == arcade::TGames::MENU)
        os << "MENU";
    else if (game == arcade::TGames::PACMAN)
        os << "PACMAN";
    else if (game == arcade::TGames::SNAKE)
        os << "SNAKE";
    else if (game == arcade::TGames::MINESWEEPER)
        os << "MINESWEEPER";
    else if (game == arcade::TGames::NIBBLER)
        os << "NIBBLER";
    else if (game == arcade::TGames::QIX)
        os << "QIX";
    else if (game == arcade::TGames::CENTIPEDE)
        os << "CENTIPEDE";
    else if (game == arcade::TGames::SOLARFOX)
        os << "SOLARFOX";
    else if (game == arcade::TGames::SOKOBAN)
        os << "SOKOBAN";
    else if (game == arcade::TGames::SPACE_INVADER)
        os << "SPACE_INVADER";
    else if (game == arcade::TGames::TETRIS)
        os << "TETRIS";
    else if (game == arcade::TGames::THE_SHOW)
        os << "THE_SHOW";
    else
        os << "UNKNOWN";
    return os;
}