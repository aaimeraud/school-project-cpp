#include "ObstacleManager.hpp"

ObstacleManager::ObstacleManager(float winWidth, float winHeight, float gap, float obstacleSpacing, int count)
    : windowWidth(winWidth), windowHeight(winHeight), gapSize(gap), spacing(obstacleSpacing), numObstacles(count)
{
    // Créer les obstacles avec un espacement initial
    for (int i = 0; i < numObstacles; i++)
    {
        float startX = windowWidth + (i * spacing);
        obstacles.push_back(new Obstacle(startX, gapSize, windowHeight, windowWidth));
    }
}

ObstacleManager::~ObstacleManager()
{
    for (Obstacle *obstacle : obstacles)
    {
        delete obstacle;
    }
    obstacles.clear();
}

void ObstacleManager::update(float deltaTime)
{
    for (Obstacle *obstacle : obstacles)
    {
        obstacle->update(deltaTime);

        // Si l'obstacle est sorti de l'écran, le repositionner à droite
        if (obstacle->isOffScreen())
        {
            // Trouver l'obstacle le plus à droite
            float maxX = 0;
            for (Obstacle *o : obstacles)
            {
                if (o->getX() > maxX)
                {
                    maxX = o->getX();
                }
            }
            // Repositionner après le dernier obstacle
            obstacle->reset(maxX + spacing);
        }
    }
}

void ObstacleManager::draw(sf::RenderWindow &window)
{
    for (Obstacle *obstacle : obstacles)
    {
        obstacle->draw(window);
    }
}

void ObstacleManager::reset()
{
    // Repositionner tous les obstacles à leur position initiale
    for (int i = 0; i < numObstacles; i++)
    {
        float startX = windowWidth + (i * spacing);
        obstacles[i]->reset(startX);
    }
}

std::vector<Obstacle *> &ObstacleManager::getObstacles()
{
    return obstacles;
}
