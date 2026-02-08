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
    bool scored; // Déjà compté dans le score
    sf::Texture texture;
    sf::Sprite *spriteTop;    // Tuyau du haut (inversé)
    sf::Sprite *spriteBottom; // Tuyau du bas
    std::mt19937 rng;         // Générateur aléatoire

    void randomizeGapY(); // Génère une nouvelle position Y pour le gap
    void updateSprites(); // Met à jour les positions des sprites

public:
    Obstacle(float x, float gap, float winHeight, float winWidth); // Crée les obstacles

    void update(float deltaTime); // deltaTime : Temps écoulé entre deux images du jeu
    void move(float deltaX);      // Déplacement horizontal

    void reset(float newX); // Repositionne l'obstacle à une nouvelle position X

    sf::FloatRect getBounds() const; // La collision
    bool isOffScreen() const;        // Savoir s'il faut supprimer l'obstacle

    void draw(sf::RenderWindow &window); // Display les obstacles

    float getX() const;
    float getGapY() const;
    float getGapSize() const;

    sf::FloatRect getTopBounds() const;    // Collision tuyau haut
    sf::FloatRect getBottomBounds() const; // Collision tuyau bas
    bool hasScored() const;                // Déjà compté?
    void setScored();                      // Marquer comme compté
};

#endif