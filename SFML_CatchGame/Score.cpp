#include "Score.h"
#include <iostream>

Score::Score(sf::RenderWindow& Window, const std::string& fontFolderPath) :
	Window(Window)
{
	if (!font.loadFromFile(fontFolderPath + "arial.ttf"))
	{
		std::cerr << "Error loading font " << fontFolderPath + "arial.ttf" << "\n";
		return;
	}
	Text.setFont(font);
	Text.setCharacterSize(20);
	Text.setStyle(sf::Text::Bold);
	Text.setPosition(10,15);
}

void Score::update()
{
	Text.setString(std::to_string(score));
}

void Score::render()
{
	Window.draw(Text);
}

void Score::increaseScore(unsigned long scoreIncrement)
{
	score += scoreIncrement;
}

void Score::reset()
{
	score = 0;
}

unsigned long Score::getScore()
{
	return score;
}
