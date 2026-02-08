#include "Ground.hpp"
#include <iostream>

using namespace std;

Ground::Ground(float winWidth, float winHeight)
    : positionX_1(0), positionX_2(0), positionX_3(0), positionY(0),
      windowWidth(winWidth), windowHeight(winHeight), speed(150.0f), textureWidth(0)
{
    if (!texture.loadFromFile("assets/flappy-bird-assets-master/sprites/base.png"))
    {
        std::cerr << "Erreur: impossible de charger la texture du sol" << std::endl;
    }

    textureWidth = static_cast<float>(texture.getSize().x);
    float textureHeight = static_cast<float>(texture.getSize().y);

    // Positionner en bas de l'écran
    positionY = windowHeight - textureHeight;

    // Initialiser les 3 sprites côte à côte
    sprite1 = new sf::Sprite(texture);
    sprite2 = new sf::Sprite(texture);
    sprite3 = new sf::Sprite(texture);

    positionX_1 = 0;
    positionX_2 = textureWidth;
    positionX_3 = textureWidth * 2;

    sprite1->setPosition({positionX_1, positionY});
    sprite2->setPosition({positionX_2, positionY});
    sprite3->setPosition({positionX_3, positionY});
}

Ground::~Ground()
{
    delete sprite1;
    delete sprite2;
    delete sprite3;
}

void Ground::update(float dt)
{
    // Déplacer tous les sprites vers la gauche
    positionX_1 -= speed * dt;
    positionX_2 -= speed * dt;
    positionX_3 -= speed * dt;

    // Trouver la position la plus à droite
    auto findRightmost = [&]() -> float
    {
        float maxX = positionX_1;
        if (positionX_2 > maxX)
            maxX = positionX_2;
        if (positionX_3 > maxX)
            maxX = positionX_3;
        return maxX;
    };

    // Quand un sprite sort complètement à gauche, le replacer à droite
    if (positionX_1 + textureWidth <= 0)
    {
        positionX_1 = findRightmost() + textureWidth;
    }
    if (positionX_2 + textureWidth <= 0)
    {
        positionX_2 = findRightmost() + textureWidth;
    }
    if (positionX_3 + textureWidth <= 0)
    {
        positionX_3 = findRightmost() + textureWidth;
    }

    sprite1->setPosition({positionX_1, positionY});
    sprite2->setPosition({positionX_2, positionY});
    sprite3->setPosition({positionX_3, positionY});
}

void Ground::draw(sf::RenderWindow &window)
{
    window.draw(*sprite1);
    window.draw(*sprite2);
    window.draw(*sprite3);
}

void Ground::reset()
{
    positionX_1 = 0;
    positionX_2 = textureWidth;
    positionX_3 = textureWidth * 2;

    sprite1->setPosition({positionX_1, positionY});
    sprite2->setPosition({positionX_2, positionY});
    sprite3->setPosition({positionX_3, positionY});
}

float Ground::getY() const
{
    return positionY;
}