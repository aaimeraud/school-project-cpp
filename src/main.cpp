#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "Game.hpp"
#include "Bird.hpp"

int main() {
    std::cout << "Dossier de travail : " << std::filesystem::current_path() << std::endl;

    Game game;
    game.start();

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Flappy Bird");
    window.setFramerateLimit(144);

    Bird bird(100.0f, 540.0f, 1080.0f);

    // === RECTANGLES DE TEST GROS ET VISIBLES ===
    sf::RectangleShape bgRect(sf::Vector2f(1920.f, 1080.f));
    bgRect.setFillColor(sf::Color(100, 150, 255));  // ciel bleu

    sf::RectangleShape groundRect1(sf::Vector2f(800.f, 150.f));  // GROS vert
    groundRect1.setFillColor(sf::Color::Green);
    groundRect1.setPosition(sf::Vector2f(0.f, 930.f));

    sf::RectangleShape groundRect2(sf::Vector2f(800.f, 150.f));  // GROS vert
    groundRect2.setFillColor(sf::Color::Green);
    groundRect2.setPosition(sf::Vector2f(800.f, 930.f));

    float groundSpeed = 3.0f;
    float groundY = 930.f;  // position sol

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    bird.jump();
                }
            }
        }

        bird.update();

        // === Ground qui défile ===
        groundRect1.move(sf::Vector2f(-groundSpeed, 0.f));
        groundRect2.move(sf::Vector2f(-groundSpeed, 0.f));

        // Recyclage des rectangles
        if (groundRect1.getPosition().x <= -800.f) {
            groundRect1.setPosition(sf::Vector2f(groundRect2.getPosition().x + 800.f, groundY));
        }
        if (groundRect2.getPosition().x <= -800.f) {
            groundRect2.setPosition(sf::Vector2f(groundRect1.getPosition().x + 800.f, groundY));
        }

        // === DESSIN ===
        window.clear();
        window.draw(bgRect);        // fond bleu fixe
        window.draw(groundRect1);   // sol vert 1 (bouge)
        window.draw(groundRect2);   // sol vert 2 (bouge)
        bird.draw(window);          // oiseau jaune
        window.display();
    }
    return 0;
}
