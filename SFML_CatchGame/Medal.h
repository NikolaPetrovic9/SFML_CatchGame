#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class Medal
{
public:
    Medal(sf::RenderWindow& Window, const std::string& texturesFolderPath, std::string fontFolderPath, sf::Vector2f position);
    void render();
    void update();
    void setNextMedal();
    bool IsLastLevelReached();
    unsigned int getLevel();
    void reset();

private:
    std::vector<sf::IntRect> medalsTextureCoordinates;
    sf::RenderWindow& Window;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font font;
    sf::Text Text;
    unsigned int actualMedal;  
};

