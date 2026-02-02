#include "Background.hpp"
#include <iostream>

Background::Background(float winWidth, float winHeight)
    : windowWidth(winWidth), windowHeight(winHeight)
{
    if (!texture.loadFromFile("assets/flappy-bird-assets-master/sprites/background-day.png"))
    {
        std::cerr << "Erreur: impossible de charger la texture du fond" << std::endl;
    }
    sprite = new sf::Sprite(texture);

    // Redimensionner pour remplir la fenêtre
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = windowWidth / static_cast<float>(textureSize.x);
    float scaleY = windowHeight / static_cast<float>(textureSize.y);
    float scale = std::max(scaleX, scaleY); // Utiliser le max pour couvrir tout l'écran
    sprite->setScale({scale, scale});

    // Centrer le background
    float spriteWidth = textureSize.x * scale;
    float spriteHeight = textureSize.y * scale;
    positionX = (windowWidth - spriteWidth) / 2.0f;
    positionY = (windowHeight - spriteHeight) / 2.0f;
    sprite->setPosition({positionX, positionY});
}

void Background::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);
}