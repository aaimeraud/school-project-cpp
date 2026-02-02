#include "Background.hpp"
#include <iostream>

Background::Background(float x, float y, float winHeight)
    : positionX(x), positionY(y), windowHeight(winHeight),
      bgTexture(), bgSprite(bgTexture)
{
    if (!bgTexture.loadFromFile("assets/flappy-bird-assets-master/sprites/background-day.png"))
    {
        std::cerr << "Erreur : impossible de charger la texture du fond !" << std::endl;
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(sf::Vector2f(positionX, positionY));
}

void Background::draw(sf::RenderWindow &window)
{
    window.draw(bgSprite);
}