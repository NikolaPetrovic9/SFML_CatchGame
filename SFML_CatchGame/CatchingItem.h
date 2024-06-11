#pragma once
#include <SFML/Graphics.hpp>
class CatchingItem
{
private:
	struct CatchItem {
		sf::Sprite Sprite;
		float speed;
	};

public:
	CatchingItem(sf::RenderWindow& Window, const std::string& texturesFolderPath, float speed, unsigned int numberOfItems);
	void render();
	void update(float deltaTime);
	void increaseSpeedByPercentage(float percentage);

	void generateItem();
	void removeItem(size_t index);
	const std::vector<CatchItem>&  getSprites();
	sf::Sprite& getSprite(size_t index);
	bool removeItemsOfTheScreen();
	void reset();

private:
	sf::RenderWindow& Window;
	sf::Texture texture;
	sf::IntRect Rect;
	std::vector<CatchItem> Sprites;
	float initialSpeed;
	float speed;
	float timeSinceLastGenerate;
	float maxTimeToGenerate;
	float initialTimeToGenerate;
	unsigned int numberOfItems;
	std::vector<float> itemSpeeds; 
	
};

