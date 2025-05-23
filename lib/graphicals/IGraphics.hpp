/*
** EPITECH PROJECT, 2025
** IGraphics
** File description:
** IGraphics
*/
#ifndef IGRAPHICS_HPP_
    #define IGRAPHICS_HPP_
    #include <iostream>
    #include <vector>
    #include <string>
    #include <map>
    #include <dlfcn.h>

namespace arcade {

    enum class TGraphics {
        NCURSES,
        SDL,
        NDK,
        AA,
        CACA,
        ALLEGRO,
        X,
        GTK,
        SFML,
        IRRLICHT,
        OPENGL,
        VULKAN,
        QT,
        NONE
    };

    enum class KeyBind {
        ESC,
        A_KEY,
        Z_KEY,
        Q_KEY,
        S_KEY,
        UP_KEY,
        DOWN_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        SPACE,
        ENTER,
        MOUSE_LEFT,
        MOUSE_RIGHT,
        NONE
    };

    class IGraphics {
        public:
            virtual ~IGraphics() = default;
            virtual void Init() = 0;
            virtual arcade::KeyBind getKey() = 0;
            virtual void Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entity) = 0;
            virtual void PlaySound(std::string sound) = 0;
            virtual void Clear() = 0;
            virtual void Nuke() = 0;

        private:
    };
}

#endif /* !IGRAPHICS_HPP_ */
