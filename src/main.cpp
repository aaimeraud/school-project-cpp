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

#include "Bird.hpp"
#include "Background.hpp"
#include "Ground.hpp"
#include "Obstacle.hpp"

int main()
{

    // Format iPhone 13 Pro vertical (390 x 844 points)
    const unsigned int windowWidth = 390u;
    const unsigned int windowHeight = 800u;

    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);

    Bird bird(windowWidth * 0.2f, windowHeight / 2.0f, static_cast<float>(windowHeight));
    Background background(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    Ground ground(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
    Obstacle obstacle(
        static_cast<float>(windowWidth), // x position (bord droit)
        150.0f,                          // taille du gap
        static_cast<float>(windowHeight),
        static_cast<float>(windowWidth));

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // détecter l'appui sur la barre d'espace
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    bird.jump(); // fait sauter l'oiseau
                }
            }
        }

        bird.update();
        ground.update(dt);
        obstacle.update(dt);

        window.clear();
        background.draw(window);
        bird.draw(window);
        obstacle.draw(window);
        ground.draw(window);
        window.display();
    }
    return 0;
}
