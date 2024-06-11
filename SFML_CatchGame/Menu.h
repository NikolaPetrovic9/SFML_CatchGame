#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SoundManager.h"

class Game; 


class Menu
{

public:
	Menu(sf::RenderWindow& Window, sf::Vector2f size, std::string fontFolderPath);

	void handleInput(Game& game);
	void render(Game& Game);
	void update(float deltaTime);
	void setScoreAndLevel(unsigned int score, unsigned int level);

private:
	sf::Font font;
	sf::Text GameNameText;
	sf::Text PlayButtonText;
	sf::Text GameStatusText;
	sf::Text GameScore;

	sf::RenderWindow& Window;
	sf::RectangleShape MenuOuterShape;
	sf::RectangleShape PlayButton;
	unsigned int score;
	unsigned int level;
	std::string endScore;
	SoundManager SoundManager;
	bool soundPlayed;

private: 
	bool isMouseClickedOnRectangle(sf::RectangleShape& rectangle);
};

