#include "Medal.h"
#include <iostream>

Medal::Medal(sf::RenderWindow& Window, const std::string& texturesFolderPath, std::string fontFolderPath, sf::Vector2f position) :
	Window(Window)
{
	if (!Texture.loadFromFile(texturesFolderPath + "medals.png")) {
		std::cerr << "Error loading image " << texturesFolderPath + "medals.png" << "\n";
		return;
	}

	if (!font.loadFromFile(fontFolderPath + "arial.ttf"))
	{
		std::cerr << "Error loading font " << fontFolderPath + "arial.ttf" << "\n";
		return;
	}
	Sprite.setTexture(Texture);

	medalsTextureCoordinates = {
		sf::IntRect(176, 0, 44, 78) ,//5
		sf::IntRect(88, 0, 44, 78) ,//3
		sf::IntRect(132, 0, 44, 78) ,//4
		sf::IntRect(88, 85, 44, 78) ,//8
		sf::IntRect(44, 0, 44, 78),//2
		sf::IntRect(0, 85, 44, 78) ,//6
		sf::IntRect(132, 85, 44, 78),//9
		sf::IntRect(44, 85, 44, 78) ,//7
		sf::IntRect(0, 0, 44, 78) //1
	};
	actualMedal = 0;
	Sprite.setPosition(position);
	Sprite.setScale(1.2f, 1.2f);

	Text.setFont(font);
	Text.setStyle(sf::Text::Bold);
	Text.setCharacterSize(20);
	Text.setOrigin(Text.getLocalBounds().width / 2, Text.getLocalBounds().height / 2);
	Text.setPosition(Sprite.getPosition().x-11, Sprite.getPosition().y - 25);
}

void Medal::render()
{
	Window.draw(Sprite);
	Window.draw(Text);
}

void Medal::update()
{
	Sprite.setTextureRect(medalsTextureCoordinates[actualMedal]);
	Text.setString("Level " + std::to_string(actualMedal + 1));
}

void Medal::setNextMedal() {
	if (actualMedal < medalsTextureCoordinates.size()-1) {
		actualMedal++;
		return;
	}
}

void Medal::reset()
{
	actualMedal = 0;
}

bool Medal::IsLastLevelReached()
{
	return actualMedal >= medalsTextureCoordinates.size()-1;
}

unsigned int Medal::getLevel()
{
	return actualMedal + 1;
}

