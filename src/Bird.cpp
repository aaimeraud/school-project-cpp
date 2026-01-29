
#include "Bird.hpp"
#include <iostream>

Bird::Bird(float x, float y, float winHeight) 
    : positionX(x), positionY(y), speedY(0), windowHeight(winHeight) {
    shape.setSize(sf::Vector2f(34.0f, 24.0f));
    shape.setFillColor(sf::Color::Yellow);
}
void Bird::update() {
    speedY += 0.5f;
    positionY += speedY;
    
    // Limite basse (sol)
    if (positionY > windowHeight - 24.0f) {
        positionY = windowHeight - 24.0f;
        speedY = 0;
    }
    
    // Limite haute (plafond)
    if (positionY < 0.0f) {
        positionY = 0.0f;
        speedY = 0;
    }
}

void Bird::jump() {
    speedY = -10;
}

void Bird::draw(sf::RenderWindow& window) {
    shape.setPosition(sf::Vector2f(positionX, positionY));
    window.draw(shape);
}