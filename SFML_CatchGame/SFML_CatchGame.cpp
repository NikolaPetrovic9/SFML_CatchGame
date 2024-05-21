// SFML_CatchGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 700), "Test");
	sf::Event e;

	Player player(window, "Assets/Sprites/MainCharacter/Idle.png", 1);
	
	while (window.isOpen()) {
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}

		player.handleInput();

		window.clear(sf::Color::White);
		
		player.draw();

		window.display();
	}
}

