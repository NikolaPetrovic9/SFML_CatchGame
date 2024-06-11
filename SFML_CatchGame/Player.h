#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h";



class Player
{
public:
    Player(sf::RenderWindow& Window, const std::string& texturesFolderPath, float speed);

    void handleInput();
    void render();
    void update(float deltaTime);
    sf::Sprite& getSprite();
    sf::RectangleShape getBoundingBox() const;

private:
    sf::RenderWindow& Window;
    sf::IntRect Rect;
    sf::Sprite Sprite;
    std::vector<sf::Texture> Textures;
    Animation IdleAnimation;
    Animation WalkAnimation;
    Animation DeathAnimation;
    bool movingLeft;
    bool movingRight;
    float speed;

private:
    void movePlayer(float deltaTime, sf::Vector2f movement);
    bool inCollision(const sf::Vector2f& newPosition);
};

