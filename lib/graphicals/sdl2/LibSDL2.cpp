/*
** EPITECH PROJECT, 2025
** Lib SDL2
** File description:
** no
*/
#include "LibSDL2.hpp"
#include <iostream>
#include <filesystem>

arcade::LibSDL2::LibSDL2()
{
}

arcade::LibSDL2::~LibSDL2()
{
}

void arcade::LibSDL2::Init()
{
    this->currentSound = "";
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        exit(84);
    }
    this->window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);
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
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        exit(84);
    }
    this->font = TTF_OpenFont("assets/fonts/TheShow.ttf", 24);
    if (this->font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        TTF_Quit();
        SDL_Quit();
        exit(84);
    }
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0)
        std::cerr << "SDL_INIT Error: " << SDL_GetError() << std::endl;
    else
        this->joystick = SDL_JoystickOpen(0);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return;
    }
    Mix_AllocateChannels(16);
    this->music = nullptr;
}

arcade::KeyBind arcade::LibSDL2::getKey()
{
    SDL_Event event;
    static float deadZone = 7000.0f;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return KeyBind::ESC;
            case SDL_JOYAXISMOTION:
                if (event.jaxis.axis == 0) {
                    if (event.jaxis.value < -deadZone)
                        return KeyBind::LEFT_KEY;
                    else if (event.jaxis.value > deadZone)
                        return KeyBind::RIGHT_KEY;
                }
                if (event.jaxis.axis == 1) {
                    if (event.jaxis.value < -deadZone)
                        return KeyBind::UP_KEY;
                    else if (event.jaxis.value > deadZone)
                        return KeyBind::DOWN_KEY;
                }
                break;
            case SDL_JOYBUTTONDOWN:
                if (event.jbutton.button == 1)
                    return KeyBind::ENTER;
                if (event.jbutton.button == 2)
                    return KeyBind::SPACE;
                if (event.jbutton.button == 3)
                    return KeyBind::A_KEY;
                if (event.jbutton.button == 4)
                    return KeyBind::Q_KEY;
                if (event.jbutton.button == 5)
                    return KeyBind::S_KEY;
                if (event.jbutton.button == 0)
                    return KeyBind::Z_KEY;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: return KeyBind::ESC;
                    case SDLK_a: return KeyBind::A_KEY;
                    case SDLK_z: return KeyBind::Z_KEY;
                    case SDLK_s: return KeyBind::S_KEY;
                    case SDLK_q: return KeyBind::Q_KEY;
                    case SDLK_SPACE: return KeyBind::SPACE;
                    case SDLK_RETURN: return KeyBind::ENTER;
                    case SDLK_DOWN: return KeyBind::DOWN_KEY;
                    case SDLK_UP: return KeyBind::UP_KEY;
                    case SDLK_LEFT: return KeyBind::LEFT_KEY;
                    case SDLK_RIGHT: return KeyBind::RIGHT_KEY;
                    default: return KeyBind::NONE;
                }
        }
    }
    return KeyBind::NONE;
}

void arcade::LibSDL2::DisplayText(const std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entity)
{
    SDL_Texture *texture = nullptr;
    SDL_Color color = {255, 255, 255, 255};
    std::string text = entity.first;

    if (entity.first.find("*RED*") != std::string::npos) {
        text = entity.first.substr(5);
        color = {255, 0, 0, 255};
    }
    auto it = this->textureCache.find(entity.first);
    if (it != this->textureCache.end()) {
        texture = it->second;
    } else {
        SDL_Surface *surface = TTF_RenderText_Solid(this->font, text.c_str(), color);
        if (surface == nullptr) {
            std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
            return;
        }
        texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            return;
        }
        this->textureCache[entity.first] = texture;
    }
    SDL_Rect rect = {entity.second.first.first, entity.second.first.second, entity.second.second.first, entity.second.second.second};
    SDL_RenderCopy(this->renderer, texture, nullptr, &rect);
}

void arcade::LibSDL2::DisplayImage(const std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entity)
{
    SDL_Texture *texture = nullptr;

    auto it = this->textureCache.find(entity.first);
    if (it != this->textureCache.end()) {
        texture = it->second;
    } else {
        SDL_Surface *surface = IMG_Load(entity.first.c_str());
        if (surface == nullptr) {
            std::cerr << "IMG_Load Error: " << SDL_GetError() << std::endl;
            return;
        }
        texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            return;
        }
        this->textureCache[entity.first] = texture;
    }
    SDL_Rect rect = {entity.second.first.first, entity.second.first.second, entity.second.second.first, entity.second.second.second};
    SDL_RenderCopy(this->renderer, texture, nullptr, &rect);
}

void arcade::LibSDL2::Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entity)
{
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);
    for (auto &entity : entity) {
        if (entity.first.find("assets/") != std::string::npos)
            DisplayImage(entity);
    }
    for (auto &entity : entity) {
        if (entity.first.find("assets/") == std::string::npos)
            DisplayText(entity);
    }
    SDL_RenderPresent(this->renderer);
}

void arcade::LibSDL2::PlaySound(std::string sound)
{
    if (sound == this->currentSound) {
        return;
    }
    this->currentSound = sound;
    this->music = Mix_LoadMUS(sound.c_str());
    if (this->music == nullptr) {
        std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
        return;
    }
    if (Mix_PlayMusic(this->music, -1) == -1) {
        std::cerr << "Mix_PlayMusic Error: " << Mix_GetError() << std::endl;
        return;
    }
    if (Mix_VolumeMusic(MIX_MAX_VOLUME / 2) == -1) {
        std::cerr << "Mix_VolumeMusic Error: " << Mix_GetError() << std::endl;
        return;
    }
}

void arcade::LibSDL2::Clear()
{
    SDL_RenderClear(this->renderer);
}

void arcade::LibSDL2::Nuke()
{
    for (auto &texture : this->textureCache)
        if (texture.second)
            SDL_DestroyTexture(texture.second);
    this->textureCache.clear();
    if (this->font) {
        TTF_CloseFont(this->font);
        this->font = nullptr;
    }
    if (this->joystick) {
        SDL_JoystickClose(this->joystick);
        this->joystick = nullptr;
    }
    if (this->music)
        Mix_HaltMusic();
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

extern "C" arcade::IGraphics *entryPoint()
{
    std::cout << "initialize sdl2" << std::endl;
    return new arcade::LibSDL2();
}
