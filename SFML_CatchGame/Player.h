#pragma once

#include <SFML/Graphics.hpp>
class Player
{
public:
    Player(sf::RenderWindow& window, const std::string& textureFile, float speed);

    void handleInput();
    void draw();

private:
    sf::RenderWindow& window;
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

 
    void moveLeft();
    void moveRight();
    void animate();
    bool leftCollision(float position, float leftBound);
    bool rightCollision(float position, float rightBound);
};

