#include "Menu.h"
#include "Game.h"

Menu::Menu(sf::RenderWindow& Window, sf::Vector2f size, std::string fontFolderPath) :
	Window(Window)
{
	MenuOuterShape.setSize(size);
	MenuOuterShape.setOrigin(MenuOuterShape.getLocalBounds().width / 2, MenuOuterShape.getLocalBounds().height / 2);
	MenuOuterShape.setPosition(Window.getSize().x / 2, Window.getSize().y / 2);
	MenuOuterShape.setFillColor(sf::Color(95, 201, 191, 170));

	PlayButton.setSize(sf::Vector2f(200, 70));
	PlayButton.setOrigin(PlayButton.getLocalBounds().width / 2, PlayButton.getLocalBounds().height / 2);
	PlayButton.setPosition(MenuOuterShape.getPosition().x, MenuOuterShape.getPosition().y - 30);
	PlayButton.setFillColor(sf::Color(220, 131, 37));


	if (!font.loadFromFile(fontFolderPath + "arial.ttf"))
	{
		std::cerr << "Error loading font " << fontFolderPath + "arial.ttf" << "\n";
		return;
	}
	PlayButtonText.setFont(font);
	PlayButtonText.setString("Play");
	PlayButtonText.setCharacterSize(42);
	PlayButtonText.setOrigin(PlayButtonText.getLocalBounds().width / 2, PlayButtonText.getLocalBounds().height / 2);
	PlayButtonText.setPosition(PlayButton.getPosition().x, PlayButton.getPosition().y - 10);

	GameNameText.setFont(font);
	GameNameText.setString("Bone Hunt");
	GameNameText.setFillColor(sf::Color(20, 20, 10));
	GameNameText.setCharacterSize(22);
	GameNameText.setOrigin(GameNameText.getLocalBounds().width / 2, GameNameText.getLocalBounds().height / 2);
	GameNameText.setPosition(MenuOuterShape.getPosition().x, MenuOuterShape.getPosition().y - 85);

	GameScore.setFont(font);
	GameScore.setString("");
	GameScore.setFillColor(sf::Color(20, 20, 10));
	GameScore.setCharacterSize(20);
	GameScore.setOrigin(GameScore.getLocalBounds().width / 2, GameScore.getLocalBounds().height / 2);
	GameScore.setPosition(MenuOuterShape.getPosition().x, MenuOuterShape.getPosition().y + 20);

	GameStatusText.setFont(font);
	GameStatusText.setString("Start Game");
	GameStatusText.setFillColor(sf::Color(20, 20, 10));
	GameStatusText.setCharacterSize(42);
	GameStatusText.setOrigin(GameStatusText.getLocalBounds().width / 2, GameStatusText.getLocalBounds().height / 2);
	GameStatusText.setPosition(MenuOuterShape.getPosition().x, MenuOuterShape.getPosition().y + 50);
}

void Menu::handleInput(Game& Game) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (Game.getState() != Game::Playing)) {
		if (isMouseClickedOnRectangle(PlayButton) && !soundPlayed) {
			Game.setState(Game::Reseting);
			SoundManager.playSound("click", 70.0f);
			soundPlayed = true;
		}
	}
	else {
		soundPlayed = false;
	}
	
}

void Menu::render(Game& Game)
{
	if (Game.getState() != Game::Playing) {
		Window.draw(MenuOuterShape);
		Window.draw(PlayButton);
		Window.draw(PlayButtonText);
		Window.draw(GameNameText);
		Window.draw(GameStatusText);
		
	}
	if (Game.getState() == Game::GameOver) {
		GameScore.setString(endScore);
		GameScore.setOrigin(GameScore.getLocalBounds().width / 2, GameScore.getLocalBounds().height / 2);
		GameStatusText.setString("Game Over");
		Window.draw(GameScore);
	}
	
}

void Menu::update(float deltaTime)
{

}

void Menu::setScoreAndLevel(unsigned int score, unsigned int level)
{
	(*this).score = score;
	(*this).level = level;
	
	endScore = "Score " + std::to_string(score) + " - Level " + std::to_string(level);
}

bool Menu::isMouseClickedOnRectangle(sf::RectangleShape& rectangle) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(Window);
	sf::Vector2f mousePosFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

	return rectangle.getGlobalBounds().contains(mousePosFloat);
}
