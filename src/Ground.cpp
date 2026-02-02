#include "Ground.hpp"
#include <iostream>

using namespace std;

Ground::Ground(float winWidth, float winHeight)
    : positionX_1(0), positionX_2(0), positionY(0), windowWidth(winWidth), windowHeight(winHeight), speed(150.0f)
{
    if (!texture.loadFromFile("assets/flappy-bird-assets-master/sprites/base.png"))
    {
        std::cerr << "Erreur: impossible de charger la texture du sol" << std::endl;
    }

    sprite1 = new sf::Sprite(texture);
    sprite2 = new sf::Sprite(texture);

    // Positionner en bas de l'écran
    float textureHeight = static_cast<float>(texture.getSize().y);
    positionY = windowHeight - textureHeight;

    positionX_1 = 0;
    positionX_2 = static_cast<float>(texture.getSize().x);

    sprite1->setPosition({positionX_1, positionY});
    sprite2->setPosition({positionX_2, positionY});
}

void Ground::update(float dt)
{
    float textureWidth = static_cast<float>(texture.getSize().x);

    // Déplacer vers la gauche avec delta time
    positionX_1 -= speed * dt;

    // Boucle infinie : reset quand sorti complètement
    if (positionX_1 <= -textureWidth)
    {
        positionX_1 += textureWidth;
    }

    // Le deuxième sprite suit toujours le premier
    positionX_2 = positionX_1 + textureWidth;

    sprite1->setPosition({positionX_1, positionY});
    sprite2->setPosition({positionX_2, positionY});
}

void Ground::draw(sf::RenderWindow &window)
{
    window.draw(*sprite1);
    window.draw(*sprite2);
}

float Ground::getY() const
{
    return positionY;
}