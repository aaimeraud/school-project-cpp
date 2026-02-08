#ifndef OBSTACLEMANAGER_HPP
#define OBSTACLEMANAGER_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Obstacle.hpp"

class ObstacleManager
{
private:
    std::vector<Obstacle *> obstacles;
    float windowWidth;
    float windowHeight;
    float gapSize;
    float spacing;
    int numObstacles;

public:
    ObstacleManager(float winWidth, float winHeight, float gap, float obstacleSpacing, int count);
    ~ObstacleManager();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void reset();

    std::vector<Obstacle *> &getObstacles();
};

#endif
