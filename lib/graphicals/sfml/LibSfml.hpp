/*
** EPITECH PROJECT, 2025
** LibSfml
** File description:
** LibSfml
*/
#ifndef LIB_SFML_HPP_
    #define LIB_SFML_HPP_
    #include "../IGraphics.hpp"
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Window.hpp>

namespace arcade{

    class LibSfml : public IGraphics {
        public:
            LibSfml();
            ~LibSfml();
            void Init() override;
            arcade::KeyBind getKey() override;
            void Display(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities) override;
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;

        private:
            sf::RenderWindow *window;
            sf::Event event;
            sf::Music music;
    };
}

#endif /* !LIB_SFML_HPP_ */
