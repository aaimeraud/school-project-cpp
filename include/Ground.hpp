#ifndef GROUND_HPP
#define GROUND_HPP

#include <SFML/Graphics.hpp>

class Ground
{
private:
    float positionX_1;
    float positionX_2;
    float positionX_3; // Troisième sprite pour éviter les gaps
    float positionY;
    float windowWidth;
    float windowHeight;
    float speed;
    float textureWidth;
    sf::Texture texture;
    sf::Sprite *sprite1;
    sf::Sprite *sprite2;
    sf::Sprite *sprite3;

public:
    Ground(float winWidth, float winHeight);
    ~Ground();

    void update(float dt); // définit le movement avec delta time

    void draw(sf::RenderWindow &window); // Dessine le fond
    void reset();                        // Réinitialiser les positions
    float getY() const;                  // Détecter les collisions
};

#endif