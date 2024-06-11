#include "CatchingItem.h"
#include <iostream>
#include <random>

CatchingItem::CatchingItem(sf::RenderWindow& Window, const std::string& texturesFolderPath, float speed, unsigned int numberOfItems) :
	Window(Window), speed(speed), numberOfItems(numberOfItems), maxTimeToGenerate(2.0f)
{	
	initialSpeed = speed;
	if (!texture.loadFromFile(texturesFolderPath + "Bone.png")) {
		std::cerr << "Error loading image " << texturesFolderPath + "Bone.png" << std::endl;
		return;
	}
	initialTimeToGenerate = maxTimeToGenerate;
	timeSinceLastGenerate = 0;
	generateItem();
}

void CatchingItem::render() {

	for (size_t i = 0; i < Sprites.size(); i++)
	{
		Window.draw(Sprites[i].Sprite);
	}
}

void CatchingItem::update(float deltaTime) {
	for (size_t i = 0; i < Sprites.size(); i++)
	{	
		Sprites[i].Sprite.move(sf::Vector2f(0, Sprites[i].speed * deltaTime));
	
		Sprites[i].Sprite.rotate(Sprites[i].speed * deltaTime);
	}

	timeSinceLastGenerate += deltaTime;
	if (timeSinceLastGenerate >= maxTimeToGenerate) {
		generateItem();
		timeSinceLastGenerate = 0.0f;
	}
}

void CatchingItem::increaseSpeedByPercentage(float percentage)
{
	speed += ((percentage / 100) * speed);
	maxTimeToGenerate -= ((percentage / 100) * maxTimeToGenerate);
}

void CatchingItem::removeItem(size_t index) {
	if (index < Sprites.size()) {
		Sprites.erase(Sprites.begin() + index);
	}
}

sf::Sprite& CatchingItem::getSprite(size_t index) {
	if (index < Sprites.size()) {
		return Sprites[index].Sprite;
	}
	throw std::out_of_range("Index out of range");
}

const std::vector<CatchingItem::CatchItem>& CatchingItem::getSprites()
{
	return Sprites;
}
bool CatchingItem::removeItemsOfTheScreen() {
	for (auto it = Sprites.begin(); it != Sprites.end(); ++it) {
		if (it -> Sprite.getPosition().y > Window.getSize().y) {
			Sprites.erase(it);
			return true;
		}
	}
	return false;
}
void CatchingItem::generateItem() {
	std::random_device rd;
	std::mt19937 gen(rd());
	unsigned int maxIncrements = (Window.getSize().x-5) / 10;
	std::uniform_int_distribution<> dis(5, maxIncrements);
	std::uniform_real_distribution<float> speedDis(speed, speed + 20.0f);

	sf::Sprite newSprite;
	newSprite.setTexture(texture);
	newSprite.setScale(0.8f, 0.8f);
	newSprite.setOrigin(newSprite.getGlobalBounds().width / 2, newSprite.getGlobalBounds().height / 2);
	newSprite.setPosition(sf::Vector2f(dis(gen) * 10, 0));

	CatchItem newItem{ newSprite, speedDis(gen) };
	Sprites.push_back(newItem);
}

void CatchingItem::reset() {
	Sprites.clear();
	generateItem();
	maxTimeToGenerate = initialTimeToGenerate;
	speed = initialSpeed;
}