#include "Player.h"
#include <iostream>

Player::Player(sf::RenderWindow& Window, const std::string& texturesFolderPath, float speed) :
	speed(speed), Window(Window),
	IdleAnimation(Sprite, 0.18),
	WalkAnimation(Sprite, 0.18),
	DeathAnimation(Sprite, 0.18)
{
	sf::Texture idleTexture, walkTexture, deathTexture;
	if (!idleTexture.loadFromFile(texturesFolderPath + "Idle.png")) {
		std::cerr << "Error loading image " << texturesFolderPath + "Idle.png" << "\n";
	}
	else {
		Textures.push_back(idleTexture);
	}

	if (!walkTexture.loadFromFile(texturesFolderPath + "Walk.png")) {
		std::cerr << "Error loading image " << texturesFolderPath + "Walk.png" << "\n";
	}
	else {
		Textures.push_back(walkTexture);
	}

	if (!deathTexture.loadFromFile(texturesFolderPath + "Death.png")) {
		std::cerr << "Error loading image " << texturesFolderPath + "Death.png" << "\n";
	}
	else {
		Textures.push_back(deathTexture);
	}
	
	Sprite.setTexture(Textures[0]);
	
	Sprite.setScale(sf::Vector2f(2.5f, 2.5f));
	Sprite.setPosition(Sprite.getGlobalBounds().width / 2, Window.getSize().y - Sprite.getGlobalBounds().height*1.5);
	
	//Animation setup
	IdleAnimation.addFrame(sf::IntRect(0, 24, 48, 24));
	IdleAnimation.addFrame(sf::IntRect(48, 24, 48, 24));
	IdleAnimation.addFrame(sf::IntRect(96, 24, 48, 24));
	IdleAnimation.addFrame(sf::IntRect(144, 24, 48, 24));

	WalkAnimation.addFrame(sf::IntRect(0, 24, 48, 24));
	WalkAnimation.addFrame(sf::IntRect(48, 24, 48, 24));
	WalkAnimation.addFrame(sf::IntRect(96, 24, 48, 24));
	WalkAnimation.addFrame(sf::IntRect(144, 24, 48, 24));

	DeathAnimation.addFrame(sf::IntRect(0, 24, 48, 24));
	DeathAnimation.addFrame(sf::IntRect(48, 24, 48, 24));
	DeathAnimation.addFrame(sf::IntRect(96, 24, 48, 24));
	DeathAnimation.addFrame(sf::IntRect(144, 24, 48, 24));
}
void Player::handleInput() {
	movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}
void Player::render() {
	Window.draw(Sprite);
}

void Player::update(float deltaTime) {
	sf::Vector2f movement(0.f, 0.f);

	if (movingRight) {
		movement.x += speed;
	}
	if (movingLeft) {
		movement.x -= speed;
	}

	Sprite.setOrigin(sf::Vector2f(Sprite.getLocalBounds().width, Sprite.getLocalBounds().height) / 2.f);

	if (movingLeft || movingRight) {
		Sprite.setTexture(Textures[1]);
		WalkAnimation.update(deltaTime);
	}
	else {
		Sprite.setTexture(Textures[0]);
		IdleAnimation.update(deltaTime);
	}
	movePlayer(deltaTime, movement);
}

void Player::movePlayer(float deltaTime, sf::Vector2f movement) {

	sf::Vector2f newPosition = Sprite.getPosition() + movement * deltaTime;

	if (movingLeft) {
		Sprite.setScale(-2.5f, 2.5f);
	}
	if (movingRight) {
		Sprite.setScale(2.5f, 2.5f);
	}
	
	if (!inCollision(newPosition)) {
		Sprite.move(movement * deltaTime);
	}
}
bool Player::inCollision(const sf::Vector2f& newPosition) {
	float left = newPosition.x - (Sprite.getLocalBounds().width / 2);
	float right = newPosition.x + (Sprite.getLocalBounds().width / 2);

	if (left < 0 || right > Window.getSize().x) {
		return true;
	}
	return false;
}

sf::Sprite& Player::getSprite()
{
	return Sprite;
}

sf::RectangleShape Player::getBoundingBox() const {
	sf::RectangleShape boundingBox;
	boundingBox.setSize(sf::Vector2f(Sprite.getGlobalBounds().width, Sprite.getGlobalBounds().height));
	boundingBox.setPosition(Sprite.getGlobalBounds().left, Sprite.getGlobalBounds().top);
	boundingBox.setFillColor(sf::Color::Transparent);
	boundingBox.setOutlineColor(sf::Color::Red);
	boundingBox.setOutlineThickness(2.f);
	return boundingBox;
}

