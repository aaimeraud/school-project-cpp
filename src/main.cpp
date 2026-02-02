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

int main()
{
    Game game;
    game.start();

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "SFML Project");
    window.setFramerateLimit(144);

    Bird bird(100.0f, 540.0f, 1080.0f);

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

        window.clear(sf::Color::Cyan);
        bird.draw(window);
        window.display();
    }
    return 0;
}
