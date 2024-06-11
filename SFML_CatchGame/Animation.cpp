#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, float switchTime) :
	Sprite(sprite), switchTime(switchTime), totalTime(0), currentFrame(0) {}

void Animation::addFrame(sf::IntRect uvRect)
{
	Frames.push_back(uvRect);
}

void Animation::update(float deltaTime)
{
	if (Frames.empty()) return;

	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentFrame = (currentFrame + 1) % Frames.size();
		Sprite.setTextureRect(Frames[currentFrame]);
	}
}
