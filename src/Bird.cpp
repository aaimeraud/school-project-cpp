#include "Bird.hpp"
#include <iostream>

using namespace std;

Bird::Bird(float x, float y, float winHeight)
    : positionX(x), positionY(y), speedY(0), windowHeight(winHeight)
{
    sf::Texture texture;
    texture.loadFromFile("assets/flappy-bird-assets-master/sprites/bluebird-midflap.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
}

void Bird::jump()
{
    speedY = -10;
};

void Bird::update()
{
    speedY += 0.5f;
    positionY += speedY;

    // Limite (Sol)
    if (positionY > windowHeight - 24.0f)
    {
        positionY = windowHeight - 24.0f;
        speedY = 0;
    }

    // Limite (Plafond)
    if (positionY < 0.0f)
    {
        positionY = 0.0f;
        speedY = 0;
    }
}

void draw(sprite);
