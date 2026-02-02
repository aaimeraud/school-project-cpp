#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle
{
private:
    float positionX;
    float positionY;
    float windowHeight;
    float deltaTime;
    float deltaX;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Obstacle(float x, float y, float winHeight); // Crée les obstacles

    void update(float deltaTime); // deltaTime : Temps écoulé entre deux images du jeu
    void move(float deltaX);      // Déplacement horizontal

    sf::FloatRect getBounds() const; // La collision
    bool isOffScreen() const;        // Savoir s'il faut supprimer l'obstacle

    void draw(sf::RenderWindow &window); // Display les obstacles
};

#endif