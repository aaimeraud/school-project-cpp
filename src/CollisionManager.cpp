#include "CollisionManager.hpp"

bool CollisionManager::checkBirdObstacleCollision(const Bird &bird, const Obstacle &obstacle)
{
    sf::FloatRect birdBounds = bird.getBounds();

    // Vérifier collision avec le tuyau du haut
    if (birdBounds.findIntersection(obstacle.getTopBounds()).has_value())
    {
        return true;
    }

    // Vérifier collision avec le tuyau du bas
    if (birdBounds.findIntersection(obstacle.getBottomBounds()).has_value())
    {
        return true;
    }

    return false;
}

bool CollisionManager::checkBirdGroundCollision(const Bird &bird, float groundY)
{
    sf::FloatRect birdBounds = bird.getBounds();
    return (birdBounds.position.y + birdBounds.size.y) >= groundY;
}

bool CollisionManager::checkBirdCeilingCollision(const Bird &bird)
{
    return bird.getPosition().y <= 0.0f;
}
