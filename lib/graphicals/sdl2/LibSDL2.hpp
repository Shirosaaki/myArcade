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

 
 namespace arcade{
    class LibSDL2 : public IGraphics {
        public:
            LibSDL2();
            ~LibSDL2();
            void Init() override;
            KeyBind getKey() override;
            void Display(std::map<std::string, std::vector<std::pair<int, int>>> &entities) override;
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;

        protected:
        private:
            SDL_Window *window;
            SDL_Renderer *renderer;
    };
}

#endif /* !LIBSDL2_HPP_ */
