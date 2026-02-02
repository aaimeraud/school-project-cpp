#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <random>

class Obstacle
{
private:
    float positionX;
    float gapY;    // Position Y du centre du gap
    float gapSize; // Taille de l'ouverture
    float windowHeight;
    float windowWidth;
    float speed; // Vitesse de défilement
    sf::Texture texture;
    sf::Sprite *spriteTop;    // Tuyau du haut (inversé)
    sf::Sprite *spriteBottom; // Tuyau du bas
    std::mt19937 rng;         // Générateur aléatoire

public:
    Obstacle(float x, float y, float winHeight, float winWidth); // Crée les obstacles

    void update(float deltaTime); // deltaTime : Temps écoulé entre deux images du jeu
    void move(float deltaX);      // Déplacement horizontal

    void reset(); // Repositionne l'obstacle à droite avec nouvelle hauteur

    sf::FloatRect getBounds() const; // La collision
    bool isOffScreen() const;        // Savoir s'il faut supprimer l'obstacle

    void draw(sf::RenderWindow &window); // Display les obstacles

    float getX() const;
    float getGapY() const;
    float getGapSize() const;
};

#endif