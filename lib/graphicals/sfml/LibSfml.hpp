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
    #include <unordered_map>

namespace arcade{

    class LibSfml : public IGraphics {
        public:
            LibSfml();
            ~LibSfml();
            void Init() override;
            arcade::KeyBind getKey() override;
            void Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities) override;
            void PlaySound(std::string sound) override;
            void Clear() override;
            void Nuke() override;

        private:
            sf::RenderWindow *window;
            sf::Event event;
            sf::Music music;
            sf::Font font;
            std::string currentSound;
            arcade::KeyBind lastKey = arcade::KeyBind::NONE;
            std::unordered_map<std::string, sf::Texture> textureCache;
    };
}

#endif /* !LIB_SFML_HPP_ */
