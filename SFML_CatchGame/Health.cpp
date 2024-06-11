#include "Health.h"
#include <iostream>

Health::Health(sf::RenderWindow& Window, const std::string& texturesFolderPath, unsigned int startingHealth) :
	Window(Window), startingHealth(startingHealth), actualHealth(startingHealth)
{
	if (!Texture.loadFromFile(texturesFolderPath + "health.png")) {
		std::cerr << "Error loading image " << texturesFolderPath + "health.png" << "\n";
		return;
	}
}

void Health::render()
{
	for (sf::Sprite& Sprite : Sprites)
	{
		Window.draw(Sprite);
	}
}

void Health::update(bool catchItemMissed)
{
	if (catchItemMissed) {
		reduceHealth();
	}
}

void Health::generateSprites() {
	float xPos = 20;
	sf::Sprite Sprite;
	Sprite.setTexture(Texture);
	for (size_t i = 0; i < startingHealth; i++)
	{
		Sprite.setPosition(sf::Vector2f(xPos, Window.getSize().y - 40));
		xPos += 45;
		Sprites.push_back(Sprite);
	}
}

void Health::reduceHealth()
{
	if (Sprites.size() > 0) {
		Sprites.pop_back();
		actualHealth--;
	}
}

void Health::reset() {
	actualHealth = startingHealth;
	Sprites.clear();
	generateSprites();
}

unsigned int Health::getHealth()
{
	return actualHealth;
}
