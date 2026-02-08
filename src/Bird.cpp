#include "Bird.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Bird::Bird(float x, float y, float winHeight)
    : positionX(x), positionY(y), velocityY(0.0f),
      gravity(1500.0f), jumpStrength(-400.0f), windowHeight(winHeight),
      currentFrame(1), animationTimer(0.0f), animationInterval(0.1f),
      rotation(0.0f), maxRotationUp(-25.0f), maxRotationDown(90.0f),
      rotationSpeed(200.0f),
      wingSound(nullptr), hitSound(nullptr), dieSound(nullptr), pointSound(nullptr)
{
    // Charger les 3 textures d'animation
    if (!textures[0].loadFromFile("assets/flappy-bird-assets-master/sprites/bluebird-downflap.png"))
    {
        cerr << "Erreur: impossible de charger bluebird-downflap.png" << endl;
    }
    if (!textures[1].loadFromFile("assets/flappy-bird-assets-master/sprites/bluebird-midflap.png"))
    {
        cerr << "Erreur: impossible de charger bluebird-midflap.png" << endl;
    }
    if (!textures[2].loadFromFile("assets/flappy-bird-assets-master/sprites/bluebird-upflap.png"))
    {
        cerr << "Erreur: impossible de charger bluebird-upflap.png" << endl;
    }

    // Créer le sprite avec la texture du milieu
    sprite = new sf::Sprite(textures[1]);

    // Centrer l'origine pour la rotation
    sf::FloatRect bounds = sprite->getLocalBounds();
    sprite->setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
    sprite->setPosition({positionX, positionY});

    // Charger les sons
    if (wingBuffer.loadFromFile("assets/flappy-bird-assets-master/audio/wing.wav"))
    {
        wingSound = new sf::Sound(wingBuffer);
    }
    else
    {
        cerr << "Erreur: impossible de charger wing.wav" << endl;
    }
    if (hitBuffer.loadFromFile("assets/flappy-bird-assets-master/audio/hit.wav"))
    {
        hitSound = new sf::Sound(hitBuffer);
    }
    else
    {
        cerr << "Erreur: impossible de charger hit.wav" << endl;
    }
    if (dieBuffer.loadFromFile("assets/flappy-bird-assets-master/audio/die.wav"))
    {
        dieSound = new sf::Sound(dieBuffer);
    }
    else
    {
        cerr << "Erreur: impossible de charger die.wav" << endl;
    }
    if (pointBuffer.loadFromFile("assets/flappy-bird-assets-master/audio/point.wav"))
    {
        pointSound = new sf::Sound(pointBuffer);
    }
    else
    {
        cerr << "Erreur: impossible de charger point.wav" << endl;
    }
}

Bird::~Bird()
{
    delete sprite;
    delete wingSound;
    delete hitSound;
    delete dieSound;
    delete pointSound;
}

void Bird::jump()
{
    velocityY = jumpStrength;
    currentFrame = 2; // upflap
    sprite->setTexture(textures[currentFrame]);
    if (wingSound)
        wingSound->play();
}

void Bird::updateAnimation(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= animationInterval)
    {
        animationTimer = 0.0f;

        // Animation basée sur la vélocité
        if (velocityY < -50.0f)
        {
            // Monte -> upflap
            currentFrame = 2;
        }
        else if (velocityY > 150.0f)
        {
            // Tombe vite -> downflap
            currentFrame = 0;
        }
        else
        {
            // Neutre -> midflap
            currentFrame = 1;
        }

        sprite->setTexture(textures[currentFrame]);
    }
}

void Bird::updateRotation(float deltaTime)
{
    if (velocityY < 0.0f)
    {
        // Monte -> rotation vers le haut (négative)
        rotation -= rotationSpeed * deltaTime;
        if (rotation < maxRotationUp)
        {
            rotation = maxRotationUp;
        }
    }
    else
    {
        // Descend -> rotation vers le bas (positive), plus lente
        rotation += rotationSpeed * deltaTime * 0.6f;
        if (rotation > maxRotationDown)
        {
            rotation = maxRotationDown;
        }
    }

    sprite->setRotation(sf::degrees(rotation));
}

void Bird::update(float deltaTime)
{
    // Appliquer la gravité
    velocityY += gravity * deltaTime;
    positionY += velocityY * deltaTime;

    // Limite (Sol)
    float birdHeight = sprite->getLocalBounds().size.y;
    if (positionY > windowHeight - birdHeight / 2.0f)
    {
        positionY = windowHeight - birdHeight / 2.0f;
        velocityY = 0.0f;
    }

    // Limite (Plafond)
    if (positionY < birdHeight / 2.0f)
    {
        positionY = birdHeight / 2.0f;
        velocityY = 0.0f;
    }

    // Mettre à jour l'animation et la rotation
    updateAnimation(deltaTime);
    updateRotation(deltaTime);

    // Mettre à jour la position du sprite
    sprite->setPosition({positionX, positionY});
}

void Bird::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);
}

sf::FloatRect Bird::getBounds() const
{
    return sprite->getGlobalBounds();
}

sf::Vector2f Bird::getPosition() const
{
    return sf::Vector2f(positionX, positionY);
}

void Bird::reset(float x, float y)
{
    positionX = x;
    positionY = y;
    velocityY = 0.0f;
    rotation = 0.0f;
    currentFrame = 1;
    sprite->setTexture(textures[currentFrame]);
    sprite->setRotation(sf::degrees(0.0f));
    sprite->setPosition({positionX, positionY});
}

void Bird::updateIdle(float deltaTime)
{
    // Animation de flottement doux (oscillation sinusoïdale)
    static float idleTime = 0.0f;
    idleTime += deltaTime;

    float baseY = windowHeight / 2.0f;
    float oscillation = std::sin(idleTime * 3.0f) * 8.0f;
    positionY = baseY + oscillation;

    // Animation des ailes (cycle normal)
    animationTimer += deltaTime;
    if (animationTimer >= animationInterval)
    {
        animationTimer = 0.0f;
        currentFrame = (currentFrame + 1) % 3;
        sprite->setTexture(textures[currentFrame]);
    }

    // Pas de rotation en mode idle
    rotation = 0.0f;
    sprite->setRotation(sf::degrees(0.0f));

    // Mettre à jour la position du sprite
    sprite->setPosition({positionX, positionY});
}

void Bird::playHitSound()
{
    if (hitSound)
        hitSound->play();
}

void Bird::playDieSound()
{
    if (dieSound)
        dieSound->play();
}

void Bird::playPointSound()
{
    if (pointSound)
        pointSound->play();
}