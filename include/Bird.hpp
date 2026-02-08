#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

class Bird
{
private:
    // Position et physique
    float positionX;
    float positionY;
    float velocityY;
    float gravity;
    float jumpStrength;
    float windowHeight;

    // Sprites (3 états d'animation)
    std::array<sf::Texture, 3> textures; // downflap, midflap, upflap
    sf::Sprite *sprite;
    int currentFrame;
    float animationTimer;
    float animationInterval;

    // Rotation
    float rotation;
    float maxRotationUp;
    float maxRotationDown;
    float rotationSpeed;

    // Sons
    sf::SoundBuffer wingBuffer;
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer dieBuffer;
    sf::SoundBuffer pointBuffer;
    sf::Sound *wingSound;
    sf::Sound *hitSound;
    sf::Sound *dieSound;
    sf::Sound *pointSound;

    void updateAnimation(float deltaTime);
    void updateRotation(float deltaTime);

public:
    Bird(float x, float y, float winHeight);
    ~Bird();

    void jump();                         // Commande pour faire sauter l'oiseau
    void update(float deltaTime);        // Mise à jour avec delta time
    void draw(sf::RenderWindow &window); // Dessine l'oiseau

    sf::FloatRect getBounds() const;  // Pour les collisions
    sf::Vector2f getPosition() const; // Position actuelle
    void reset(float x, float y);     // Réinitialiser l'oiseau

    void updateIdle(float deltaTime); // Animation d'attente (flottement)

    // Sons
    void playHitSound();
    void playDieSound();
    void playPointSound();
};

#endif