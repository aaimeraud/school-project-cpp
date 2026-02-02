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
#include "Game.hpp"
#include "Bird.hpp"
#include "Background.hpp"

int main()
{
    Game game;
    game.start();

    // Format iPhone 13 Pro vertical (390 x 844 points)
    const unsigned int windowWidth = 390u;
    const unsigned int windowHeight = 844u;

    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Flappy Bird");
    window.setFramerateLimit(144);

    Bird bird(windowWidth * 0.2f, windowHeight / 2.0f, static_cast<float>(windowHeight));
    Background background(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

    while (window.isOpen())
    {

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

        window.clear();
        background.draw(window); 
        bird.draw(window);       
        window.display();
    }
    return 0;
}
