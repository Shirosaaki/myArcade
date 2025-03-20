/*
** EPITECH PROJECT, 2025
** Lib SDL2
** File description:
** no
*/

#include "LibSDL2.hpp"


arcade::LibSDL2::LibSDL2()
{
    Init();
}

arcade::LibSDL2::~LibSDL2()
{
}

void arcade::LibSDL2::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    this->window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (this->window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(84);
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        SDL_DestroyWindow(this->window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(84);
    }
}

arcade::KeyBind arcade::LibSDL2::getKey()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return KeyBind::ESC;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return KeyBind::ESC;
            case SDLK_a:
                return KeyBind::A_KEY;
            case SDLK_z:
                return KeyBind::Z_KEY;
            case SDLK_SPACE:
                return KeyBind::SPACE;
            case SDLK_RETURN:
                return KeyBind::ENTER;
            case SDLK_DOWN:
                return KeyBind::DOWN_KEY;
            case SDLK_UP:
                return KeyBind::UP_KEY;
            case SDLK_LEFT:
                return KeyBind::LEFT_KEY;
            case SDLK_RIGHT:
                return KeyBind::RIGHT_KEY;
            default:
                return KeyBind::NONE;
            }
        default:
            return KeyBind::NONE;
        }
    }
    return KeyBind::NONE;
}

void arcade::LibSDL2::Display(std::map<std::string, std::vector<std::pair<int, int>>> &entities)
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    for (auto &entity : entities) {
        for (auto &pos : entity.second) {
            SDL_Rect rect = {pos.first * 20, pos.second * 20, 20, 20};
            if (entity.first == "player")
                SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 255);
            else if (entity.first == "wall")
                SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
            else if (entity.first == "food")
                SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(this->renderer, &rect);
        }
    }
    SDL_RenderPresent(this->renderer);
}

void arcade::LibSDL2::PlaySound(std::string sound)
{
    (void)sound;
}

void arcade::LibSDL2::Clear()
{
    SDL_RenderClear(this->renderer);
}

void arcade::LibSDL2::Nuke()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

extern "C" arcade::IGraphics *entryPoint()
{
    std::cout << "initialize sdl2" << std::endl;
    return new arcade::LibSDL2();
}
