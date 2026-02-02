#ifndef GROUND_HPP
#define GROUND_HPP

#include <SFML/Graphics.hpp>

class Ground
{
private:
    float positionX_1;
    float positionX_2;
    float positionY;
    float windowWidth;
    float windowHeight;
    float speed;
    sf::Texture texture;
    sf::Sprite *sprite1;
    sf::Sprite *sprite2;

public:
    Ground(float winWidth, float winHeight);

    void update(float dt); // définit le movement avec delta time

    void draw(sf::RenderWindow &window); // Dessine le fond
    float getY() const;                  // Détecter les collisions
};

#endif