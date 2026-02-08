#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include "Bird.hpp"
#include "Obstacle.hpp"

class CollisionManager
{
public:
    // Vérifie collision oiseau avec un obstacle (haut ou bas)
    static bool checkBirdObstacleCollision(const Bird &bird, const Obstacle &obstacle);

    // Vérifie collision oiseau avec le sol
    static bool checkBirdGroundCollision(const Bird &bird, float groundY);

    // Vérifie collision oiseau avec le plafond
    static bool checkBirdCeilingCollision(const Bird &bird);
};

#endif
