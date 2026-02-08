#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>

class Bird
{
private:
    float positionX;
    float positionY;
    float speedY;
    float windowHeight;
    sf::Texture texture;
    sf::Sprite *sprite;

public:
    Bird(float x, float y, float winHeight);

    void jump(); // Commande pour faire sauter l'oiseau

    void update(); // Initialisation de la gravité

    void draw(sf::RenderWindow &window); // Dessine l'oiseau

    sf::FloatRect getBounds() const;  // Pour les collisions
    sf::Vector2f getPosition() const; // Position actuelle
    void reset(float x, float y);     // Réinitialiser l'oiseau
};

#endif