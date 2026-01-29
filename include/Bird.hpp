#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>


// Responsabilité : Gérer l’oiseau (position, gravité, saut)
class Bird{
    private:
        float positionX;
        float positionY;
        float speedY;
        // sf::Texture texture;
        // sf::Sprite sprite;
        sf::RectangleShape shape;
        float windowHeight;

    public:
        Bird(float x, float y, float winHeight);

        // update() se lance à chaque frames 
        void update();

        // la fonction jump() modifie la vitesse de chute de l'oiseau en enlevant 10 à 
        void jump();

        // Draw() dessine l'oiseau
        void draw(sf::RenderWindow& window);
        
        // update()  : applique la gravité, met à jour la position
        //  jump()  : fait sauter l’oiseau
        //  draw()  : dessine l’oiseau à l’écran

};

#endif