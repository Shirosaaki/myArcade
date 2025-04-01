/*
** EPITECH PROJECT, 2025
** Lib SDL2
** File description:
** no
*/

#ifndef LIBSDL2_HPP_
    #define LIBSDL2_HPP_
    #include "../IGraphics.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_video.h>
    #include <SDL2/SDL_render.h>
    #include <SDL2/SDL_events.h>
    #include <SDL2/SDL_audio.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_gamecontroller.h>
    #include <unordered_map>
 
 namespace arcade {
    class LibSDL2 : public IGraphics {
        public:
            LibSDL2();
            ~LibSDL2();
            void Init() override;
            arcade::KeyBind getKey() override;
            void Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entity) override;
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;

        protected:
            void DisplayText(const std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entity);
            void DisplayImage(const std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entity);

        private:
            SDL_Window *window;
            SDL_Renderer *renderer;
            TTF_Font *font;
            SDL_Rect rect;
            Mix_Music *music;
            std::unordered_map<std::string, SDL_Texture*> textureCache;
            std::string currentSound;
            SDL_Joystick *joystick;
            arcade::KeyBind lastKey = arcade::KeyBind::NONE;
    };
}

#endif /* !LIBSDL2_HPP_ */
