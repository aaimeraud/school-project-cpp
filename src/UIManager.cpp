#include "UIManager.hpp"
#include <iostream>

UIManager::UIManager(float winWidth, float winHeight)
    : messageSprite(nullptr), gameOverSprite(nullptr),
      windowWidth(winWidth), windowHeight(winHeight),
      currentState(GameState::Ready), currentScore(0)
{
    std::string basePath = "assets/flappy-bird-assets-master/sprites/";

    // Charger les textures des chiffres
    for (int i = 0; i < 10; ++i)
    {
        if (!digitTextures[i].loadFromFile(basePath + std::to_string(i) + ".png"))
        {
            std::cerr << "Erreur: impossible de charger " << i << ".png" << std::endl;
        }
    }

    // Charger les textures UI
    if (!messageTexture.loadFromFile(basePath + "message.png"))
    {
        std::cerr << "Erreur: impossible de charger message.png" << std::endl;
    }

    if (!gameOverTexture.loadFromFile(basePath + "gameover.png"))
    {
        std::cerr << "Erreur: impossible de charger gameover.png" << std::endl;
    }

    // Créer les sprites UI
    messageSprite = new sf::Sprite(messageTexture);
    gameOverSprite = new sf::Sprite(gameOverTexture);

    // Centrer les sprites
    centerSprite(messageSprite, windowHeight / 4.0f);
    centerSprite(gameOverSprite, windowHeight / 3.0f);

    // Initialiser l'affichage du score
    updateScoreDisplay();
}

UIManager::~UIManager()
{
    delete messageSprite;
    delete gameOverSprite;
    clearScoreSprites();
}

void UIManager::clearScoreSprites()
{
    for (auto *sprite : scoreSprites)
    {
        delete sprite;
    }
    scoreSprites.clear();
}

void UIManager::centerSprite(sf::Sprite *sprite, float y)
{
    sf::FloatRect bounds = sprite->getGlobalBounds();
    float x = (windowWidth - bounds.size.x) / 2.0f;
    sprite->setPosition({x, y});
}

void UIManager::setState(GameState state)
{
    currentState = state;
}

void UIManager::setScore(int score)
{
    if (score != currentScore)
    {
        currentScore = score;
        updateScoreDisplay();
    }
}

void UIManager::updateScoreDisplay()
{
    clearScoreSprites();

    std::string scoreStr = std::to_string(currentScore);

    // Calculer la largeur totale du score
    float totalWidth = 0.0f;
    float digitScale = 1.5f; // Échelle des chiffres
    float spacing = 2.0f;    // Espacement entre chiffres

    for (char c : scoreStr)
    {
        int digit = c - '0';
        totalWidth += digitTextures[digit].getSize().x * digitScale + spacing;
    }
    totalWidth -= spacing; // Retirer le dernier espacement

    // Positionner les chiffres centrés en haut de l'écran
    float startX = (windowWidth - totalWidth) / 2.0f;
    float y = 30.0f; // Position Y du score
    float currentX = startX;

    for (char c : scoreStr)
    {
        int digit = c - '0';
        sf::Sprite *digitSprite = new sf::Sprite(digitTextures[digit]);
        digitSprite->setScale({digitScale, digitScale});
        digitSprite->setPosition({currentX, y});
        scoreSprites.push_back(digitSprite);

        currentX += digitTextures[digit].getSize().x * digitScale + spacing;
    }
}

void UIManager::draw(sf::RenderWindow &window)
{
    switch (currentState)
    {
    case GameState::Ready:
        window.draw(*messageSprite);
        break;

    case GameState::Playing:
        // Afficher seulement le score
        for (auto *sprite : scoreSprites)
        {
            window.draw(*sprite);
        }
        break;

    case GameState::GameOver:
        window.draw(*gameOverSprite);
        // Afficher aussi le score final
        for (auto *sprite : scoreSprites)
        {
            window.draw(*sprite);
        }
        break;
    }
}

UIManager::GameState UIManager::getState() const
{
    return currentState;
}
