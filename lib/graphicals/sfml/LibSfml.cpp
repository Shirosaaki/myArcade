/*
** EPITECH PROJECT, 2025
** LibSfml
** File description:
** LibSfml
*/
#include "LibSfml.hpp"

arcade::LibSfml::LibSfml()
{
}

arcade::LibSfml::~LibSfml()
{
}

void arcade::LibSfml::Init()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Arcade");
    this->window->setFramerateLimit(60);
}

arcade::KeyBind arcade::LibSfml::getKey()
{
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed) {
            return KeyBind::ESC;
        }
        if (this->event.type == sf::Event::KeyPressed) {
            if (this->event.key.code == sf::Keyboard::Escape)
                return KeyBind::ESC;
            if (this->event.key.code == sf::Keyboard::Z)
                return KeyBind::Z_KEY;
            if (this->event.key.code == sf::Keyboard::A)
                return KeyBind::A_KEY;
            if (this->event.key.code == sf::Keyboard::Space)
                return KeyBind::SPACE;
            if (this->event.key.code == sf::Keyboard::Return)
                return KeyBind::ENTER;
            if (this->event.key.code == sf::Keyboard::Down)
                return KeyBind::DOWN_KEY;
            if (this->event.key.code == sf::Keyboard::Up)
                return KeyBind::UP_KEY;
            if (this->event.key.code == sf::Keyboard::Left)
                return KeyBind::LEFT_KEY;
            if (this->event.key.code == sf::Keyboard::Right)
                return KeyBind::RIGHT_KEY;
        }
    }
    return KeyBind::NONE;
}

void arcade::LibSfml::Display(std::map<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> &entities)
{
    this->window->clear();
    for (auto &entity : entities) {
        continue;
        sf::Texture texture;
        sf::Sprite sprite;
        if (!texture.loadFromFile(entity.first)) {
            std::cerr << "Error loading texture: " << entity.first << std::endl;
            continue;
        }
        sprite.setTexture(texture);
        sprite.setPosition(entity.second.first.first, entity.second.first.second);
        this->window->draw(sprite);
    }
    this->window->display();
}

void arcade::LibSfml::PlaySound(std::string sound)
{
    if (!this->music.openFromFile(sound)) {
        std::cerr << "Error loading music" << std::endl;
        exit(84);
    }
    this->music.play();
}

void arcade::LibSfml::Clear()
{
    this->window->clear();
}

void arcade::LibSfml::Nuke()
{
    this->window->close();
    delete this->window;
}

extern "C" arcade::IGraphics *entryPoint()
{
    return new arcade::LibSfml();
}
