#include "Bird.hpp"
#include <iostream>

using namespace std;

Bird::Bird(float x, float y, float winHeight)
    : positionX(x), positionY(y), speedY(0), windowHeight(winHeight)
{

    if (!texture.loadFromFile("assets/flappy-bird-assets-master/sprites/bluebird-midflap.png"))
    {
        cerr << "Erreur: impossible de charger la texture" << endl;
    }
    sprite = new sf::Sprite(texture);
    sprite->setPosition({positionX, positionY});
}

void Bird::jump()
{
    speedY = -3.5;
};

void Bird::update()
{
    speedY += 0.10f;
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
    // Mettre à jour la position du sprite
    sprite->setPosition({positionX, positionY});
}

void Bird::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);
}