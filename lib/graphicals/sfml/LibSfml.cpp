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
    this->font.loadFromFile("assets/fonts/TheShow.ttf");
    this->music.setVolume(50);
    if (!sf::Joystick::isConnected(0)) {
        std::cerr << "No controller connected!" << std::endl;
    }
    else {
        sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
        if (id.vendorId == 0x045e && id.productId == 0x028e) {
            std::cout << "Controller is an Xbox controller!" << std::endl;
        }
    }
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
            if (this->event.key.code == sf::Keyboard::Q)
                return KeyBind::Q_KEY;
            if (this->event.key.code == sf::Keyboard::S)
                return KeyBind::S_KEY;
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
    if (sf::Joystick::isConnected(0)) {
        if (sf::Joystick::isButtonPressed(0, 1))
            return KeyBind::ENTER;
        if (sf::Joystick::isButtonPressed(0, 2))
            return KeyBind::SPACE;
        if (sf::Joystick::isButtonPressed(0, 3))
            return KeyBind::A_KEY;
        if (sf::Joystick::isButtonPressed(0, 4))
            return KeyBind::Q_KEY;
        if (sf::Joystick::isButtonPressed(0, 5))
            return KeyBind::S_KEY;
        if (sf::Joystick::isButtonPressed(0, 0))
            return KeyBind::Z_KEY;
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50)
            return KeyBind::LEFT_KEY;
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50)
            return KeyBind::RIGHT_KEY;
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50)
            return KeyBind::UP_KEY;
        if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50)
            return KeyBind::DOWN_KEY;
    }
    return KeyBind::NONE;
}

void arcade::LibSfml::Display(const std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>> &entities)
{
    this->window->clear();
    for (auto &entity : entities) {
        if (entity.first.find("assets/") != std::string::npos) {
            sf::Texture texture;
            sf::Sprite sprite;
            if (!texture.loadFromFile(entity.first)) {
                std::cerr << "Error loading texture: " << entity.first << std::endl;
                continue;
            }
            sprite.setTexture(texture);
            sprite.setPosition(entity.second.first.first, entity.second.first.second);
            sprite.setScale(entity.second.second.first / static_cast<float>(texture.getSize().x),
                            entity.second.second.second / static_cast<float>(texture.getSize().y));
            this->window->draw(sprite);
        }
    }
    for (auto &entity : entities) {
        if (entity.first.find("assets/") == std::string::npos) {
            sf::Text text;
            text.setFont(this->font);
            text.setString(entity.first);
            text.setCharacterSize(35);
            text.setFillColor(sf::Color::White);
            text.setPosition(entity.second.first.first, entity.second.first.second);
            if (entity.first.find("*RED*") != std::string::npos) {
                text.setString(entity.first.substr(5));
                text.setFillColor(sf::Color::Red);
            }
            this->window->draw(text);
        }
    }
    this->window->display();
}

void arcade::LibSfml::PlaySound(std::string sound)
{
    if (sound == this->currentSound) {
        return;
    }
    this->currentSound = sound;
    if (!this->music.openFromFile(sound)) {
        std::cerr << "Error: Could not load sound file: " << sound << std::endl;
        return;
    }
    this->music.play();
}

void arcade::LibSfml::Clear()
{
    this->window->clear();
}

void arcade::LibSfml::Nuke()
{
    this->music.stop();
    this->window->close();
    delete this->window;
}

extern "C" arcade::IGraphics *entryPoint()
{
    std::cout << "Loading Sfml" << std::endl;
    return new arcade::LibSfml();
}
