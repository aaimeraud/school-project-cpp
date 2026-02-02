#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>


class Background {
    private:
        float positionX;
        float positionY;
        float windowHeight;
        sf::Texture bgTexture;
        sf::Sprite bgSprite;

    public:
        Background(float x, float y, float winHeight);

        void draw(sf::RenderWindow& window); // Dessine le fond
};


#endif