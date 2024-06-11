#pragma once

#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::Sprite& Sprite, float switchTime);
	void addFrame(sf::IntRect Rect);
	void update(float deltaTime);
private:
	sf::Sprite& Sprite;
	std::vector<sf::IntRect> Frames;
	float switchTime;
	float totalTime;
	unsigned int currentFrame;
};

