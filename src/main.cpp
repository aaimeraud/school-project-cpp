                                                                                                                                                                                                                                                                                                                                                                        

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Bird.hpp"
int main() {
    std::cout << "Dossier de travail : " << std::filesystem::current_path() << std::endl;

    Game game;
    game.start();

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Flappy Bird");
    window.setFramerateLimit(144);

    Bird bird(100.0f, 540.0f, 1080.0f);  // Créer l'oiseau au centre vertical

    while (window.isOpen()) {
        // Gérer les événements
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // Détecter Espace pour sauter
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    bird.jump();
                }
            }
        }

        bird.update();
        
        // Dessiner
        window.clear(sf::Color::Black);
        bird.draw(window);
        window.display();
    }
    return 0;
}
