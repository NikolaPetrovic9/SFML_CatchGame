#pragma once

#include <SFML/Graphics.hpp>
class Score
{
public:
    Score(sf::RenderWindow& Window, const std::string& fontFolderPath);

    void render();
    void update();
    void increaseScore(unsigned long scoreIncrement);
    unsigned long getScore();
    void reset();

private:
    sf::RenderWindow& Window;
    sf::Font font;
    sf::Text Text;
    unsigned long score;
};

