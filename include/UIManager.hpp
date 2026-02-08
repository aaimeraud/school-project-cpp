#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <string>

class UIManager
{
public:
    enum class GameState
    {
        Ready,
        Playing,
        GameOver
    };

private:
    // Textures des chiffres (0-9)
    std::array<sf::Texture, 10> digitTextures;

    // Textures UI
    sf::Texture messageTexture;  // Écran "Get Ready" / instructions
    sf::Texture gameOverTexture; // Écran "Game Over"

    // Sprites UI
    sf::Sprite *messageSprite;
    sf::Sprite *gameOverSprite;

    // Score sprites (dynamiques)
    std::vector<sf::Sprite *> scoreSprites;

    // Dimensions fenêtre
    float windowWidth;
    float windowHeight;

    // État actuel
    GameState currentState;
    int currentScore;

    void updateScoreDisplay();
    void centerSprite(sf::Sprite *sprite, float y);
    void clearScoreSprites();

public:
    UIManager(float winWidth, float winHeight);
    ~UIManager();

    void setState(GameState state);
    void setScore(int score);
    void draw(sf::RenderWindow &window);

    GameState getState() const;
};

#endif
