#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include <string>
#include <SFML/Graphics.hpp>

class Obstacle {
    private:
        float positionX;
        float gapY;
        float gapHeight;
        float width;
        float windowHeight;
        sf::RectangleShape topObstacle;
        sf::RectangleShape bottomObstacle;


    public:
        Obstacle(float x, float gap, float height);

        void update();
        void draw(sf::RenderWindow& window);
        float getX() const;
};



#endif