#include "Obstacle.hpp"
#include <iostream>

using namespace std;

Obstacle::Obstacle(float x, float gap, float winHeight, float winWidth)
    : positionX(x), gapSize(gap), windowHeight(winHeight), windowWidth(winWidth), speed(150.0f), scored(false)
{
    // Initialiser le générateur aléatoire
    random_device rd;
    rng = mt19937(rd());

    if (!texture.loadFromFile("assets/flappy-bird-assets-master/sprites/pipe-red.png"))
    {
        cerr << "Erreur: impossible de charger la texture du tuyau" << endl;
    }

    spriteTop = new sf::Sprite(texture);
    spriteBottom = new sf::Sprite(texture);

    // Inverser le tuyau du haut (rotation 180°)
    spriteTop->setScale({1.0f, -1.0f});

    // Générer la position Y du gap
    randomizeGapY();
    updateSprites();
}

void Obstacle::randomizeGapY()
{
    // Gap aléatoire entre 25% et 65% de la hauteur (pour laisser place au sol)
    float minY = windowHeight * 0.25f;
    float maxY = windowHeight * 0.65f;
    uniform_real_distribution<float> dist(minY, maxY);
    gapY = dist(rng);
}

void Obstacle::updateSprites()
{
    // Dimensions de la texture
    float textureHeight = static_cast<float>(texture.getSize().y);

    // Calculer la hauteur du tuyau du haut (du plafond jusqu'au gap)
    float topPipeHeight = gapY - gapSize / 2.0f;
    float scaleTop = topPipeHeight / textureHeight;

    // Tuyau du haut : inversé, part du plafond
    spriteTop->setScale({1.0f, -scaleTop});
    spriteTop->setPosition({positionX, topPipeHeight});

    // Calculer la hauteur du tuyau du bas (du gap jusqu'au sol)
    float bottomPipeY = gapY + gapSize / 2.0f;
    float bottomPipeHeight = windowHeight - bottomPipeY;
    float scaleBottom = bottomPipeHeight / textureHeight;

    // Tuyau du bas : part du gap vers le sol
    spriteBottom->setScale({1.0f, scaleBottom});
    spriteBottom->setPosition({positionX, bottomPipeY});
}

void Obstacle::reset(float newX)
{
    positionX = newX;
    scored = false;
    randomizeGapY();
    updateSprites();
}

void Obstacle::update(float dt)
{
    // Déplacer vers la gauche
    positionX -= speed * dt;

    // Mettre à jour les positions des sprites
    updateSprites();
}

bool Obstacle::isOffScreen() const
{
    float textureWidth = static_cast<float>(texture.getSize().x);
    return positionX + textureWidth < 0;
}

void Obstacle::draw(sf::RenderWindow &window)
{
    window.draw(*spriteTop);
    window.draw(*spriteBottom);
}

float Obstacle::getX() const
{
    return positionX;
}

float Obstacle::getGapY() const
{
    return gapY;
}

float Obstacle::getGapSize() const
{
    return gapSize;
}

sf::FloatRect Obstacle::getTopBounds() const
{
    return spriteTop->getGlobalBounds();
}

sf::FloatRect Obstacle::getBottomBounds() const
{
    return spriteBottom->getGlobalBounds();
}

bool Obstacle::hasScored() const
{
    return scored;
}

void Obstacle::setScored()
{
    scored = true;
}