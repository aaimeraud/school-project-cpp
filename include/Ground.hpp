#ifndef GROUND_HPP
#define GROUND_HPP

#include <SFML/Graphics.hpp>

class Background
{
private:
    float positionX;
    float positionY;
    float windowWidth;
    float windowHeight;
    sf::Texture texture;
    sf::Sprite *sprite;

public:
    Background(float winWidth, float winHeight);

    void draw(sf::RenderWindow &window); // Dessine le fond
};

#endif