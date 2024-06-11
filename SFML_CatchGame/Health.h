#pragma once

#include <SFML/Graphics.hpp>
class Health
{
public:
    Health(sf::RenderWindow& Window, const std::string& texturesFolderPath, unsigned int startingHealth);
    void render();
    void update(bool healthReduce);
    unsigned int getHealth();
    void generateSprites();
    void reset();

private:

    sf::RenderWindow& Window;
    sf::IntRect Rect;
    std::vector<sf::Sprite> Sprites;
    sf::Texture Texture;
    unsigned int actualHealth;
    unsigned int startingHealth;

private:
    void reduceHealth();
};

