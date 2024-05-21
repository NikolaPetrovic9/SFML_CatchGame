#include "Player.h"
#include <iostream>

Player::Player(sf::RenderWindow& window, const std::string& textureFile, float speed) :
	speed(speed), window(window)
{
	if (!texture.loadFromFile(textureFile)) {
		std::cout << "error loading image";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
	sprite.setScale(sf::Vector2f(2, 2));
	sprite.setPosition(0, window.getSize().y - sprite.getGlobalBounds().height);
}
void Player::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		moveLeft();
	}
	else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		moveRight();
	}
}
void Player::draw() {
	window.draw(sprite);
}

void Player::moveLeft() {
	if (leftCollision(sprite.getPosition().x, 0))
		sprite.move(-speed, 0.0);
}

void Player::moveRight() {
	if(rightCollision(sprite.getPosition().x + sprite.getGlobalBounds().width, window.getSize().x))
		sprite.move(speed, 0.0);
}

void Player::animate()
{

}

bool Player::leftCollision(float position, float leftBound) {
	return position > leftBound;
}

bool Player::rightCollision(float position, float rightBound) {
	return position < rightBound;
	
}