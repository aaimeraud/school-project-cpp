/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini  <https://moustoifa.moumini.xyz/> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:15:46 by mmoumini          #+#    #+#             */
/*   Updated: 2026/01/26 11:39:28 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Bird.hpp"
#include "Background.hpp"
#include "Ground.hpp"
#include "ObstacleManager.hpp"
#include "CollisionManager.hpp"
#include "UIManager.hpp"

int main()
{

    // Format iPhone 13 Pro vertical (390 x 844 points)
    const unsigned int windowWidth = 390u;
    const unsigned int windowHeight = 800u;
    const float groundY = windowHeight - 112.0f; // Hauteur du sol

    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    Bird bird(windowWidth * 0.2f, windowHeight / 2.0f, static_cast<float>(windowHeight));
    Background background(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    Ground ground(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    ObstacleManager obstacleManager(
        static_cast<float>(windowWidth),
        static_cast<float>(windowHeight),
        135.0f, // taille du gap
        250.0f, // espacement entre obstacles
        3);     // nombre d'obstacles
    UIManager uiManager(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

    sf::Clock clock;
    int score = 0;
    bool gameOver = false;
    bool gameStarted = false;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        // Limiter deltaTime pour éviter les gros sauts
        if (dt > 0.05f)
            dt = 0.05f;

        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // détecter l'appui sur la barre d'espace ou clic souris
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    if (!gameStarted)
                    {
                        // Démarrer le jeu
                        gameStarted = true;
                        uiManager.setState(UIManager::GameState::Playing);
                        bird.jump();
                    }
                    else if (gameOver)
                    {
                        // Restart the game
                        bird.reset(windowWidth * 0.2f, windowHeight / 2.0f);
                        obstacleManager.reset();
                        ground.reset();
                        score = 0;
                        gameOver = false;
                        gameStarted = true;
                        uiManager.setScore(0);
                        uiManager.setState(UIManager::GameState::Playing);
                    }
                    else
                    {
                        bird.jump(); // fait sauter l'oiseau
                    }
                }
            }

            // Support du clic souris
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (!gameStarted)
                {
                    gameStarted = true;
                    uiManager.setState(UIManager::GameState::Playing);
                    bird.jump();
                }
                else if (gameOver)
                {
                    bird.reset(windowWidth * 0.2f, windowHeight / 2.0f);
                    obstacleManager.reset();
                    ground.reset();
                    score = 0;
                    gameOver = false;
                    gameStarted = true;
                    uiManager.setScore(0);
                    uiManager.setState(UIManager::GameState::Playing);
                }
                else
                {
                    bird.jump();
                }
            }
        }

        if (!gameStarted)
        {
            // Animation d'attente
            bird.updateIdle(dt);
        }
        else if (!gameOver)
        {
            bird.update(dt);
            ground.update(dt);
            obstacleManager.update(dt);

            // Vérifier les collisions
            for (Obstacle *obstacle : obstacleManager.getObstacles())
            {
                if (CollisionManager::checkBirdObstacleCollision(bird, *obstacle))
                {
                    bird.playHitSound();
                    gameOver = true;
                    uiManager.setState(UIManager::GameState::GameOver);
                    std::cout << "Game Over! Score final: " << score << std::endl;
                    break;
                }

                // Vérifier si l'oiseau a passé l'obstacle (score)
                float pipeWidth = 52.0f; // Largeur approximative du tuyau
                if (!obstacle->hasScored() && bird.getPosition().x > obstacle->getX() + pipeWidth)
                {
                    obstacle->setScored();
                    score++;
                    bird.playPointSound();
                    uiManager.setScore(score);
                    std::cout << "Score: " << score << std::endl;
                }
            }

            // Vérifier collision avec le sol
            if (CollisionManager::checkBirdGroundCollision(bird, groundY))
            {
                bird.playHitSound();
                gameOver = true;
                uiManager.setState(UIManager::GameState::GameOver);
                std::cout << "Game Over! Score final: " << score << std::endl;
            }
        }

        window.clear();
        background.draw(window);
        obstacleManager.draw(window);
        ground.draw(window);
        bird.draw(window);
        uiManager.draw(window);
        window.display();
    }
    return 0;
}
