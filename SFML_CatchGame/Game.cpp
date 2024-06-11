#include "Game.h"

Game::Game()
	: Window(sf::VideoMode(500, 700), "Bone Hunt"),
	Player(Window, "Assets/Sprites/MainCharacter/", 500),
	CatchingItem(Window, "Assets/Sprites/Game/", 50, 2), 
	Health(Window, "Assets/Sprites/Game/", 3),
	Score(Window, "Assets/Fonts/"),
	Menu(Window, sf::Vector2f(400,200), "Assets/Fonts/"),
	Medal(Window, "Assets/Sprites/Game/", "Assets/Fonts/" , sf::Vector2f(Window.getSize().x - 80, 40)),
	State(MainMenu) 
{
	pauseActive = false;;
}

void Game::run() {
	while (Window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	sf::Event e;
	while (Window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed) {
			Window.close();
		}
	}
	Player.handleInput();
	Menu.handleInput(*this);
}

void Game::update() {
	float deltaTime = clock.restart().asSeconds();
	if (State == Playing) {
		Player.update(deltaTime);
		Health.update(CatchingItem.removeItemsOfTheScreen());
		CatchingItem.update(deltaTime);
		Score.update();
		Medal.update();
		checkCollisions();
	}
	if (State == Pause) {
		totalTime += deltaTime;
		if (totalTime >= 3.0) {
			totalTime = 0;
			pauseActive = false;
			setState(Playing);
		}
	}
	checkGameState();
}

void Game::render() {
	//Load and set background to game
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Assets/Sprites/Game/Background.png")) {
		std::cerr << "Error loading background  image " << std::endl;
	}
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setPosition(0, 0);

	Window.clear(sf::Color::White);
	Window.draw(backgroundSprite);

	if (State == MainMenu) {
		Menu.render(*this);
	}
	if (State == Playing || State == Pause) {
		Player.render();
		Health.render();
		CatchingItem.render();
		Score.render();
		Medal.render();
	}
	if (State == GameOver) {
		Menu.render(*this);
		Player.render();
		Health.render();
		Score.render();
		Medal.render();
	}
	Window.display();
}

bool Game::isGameOver() {
	return (Health.getHealth() < 1);
}

void Game::checkGameState() {
	if (State == Reseting) {
		resetGame();
		setState(Playing);
	}
	if (isGameOver()) {
		if (!failSoundNotPlayed) {
			SoundManager.playSound("fail", 70);
			failSoundNotPlayed = true;
		}
		Menu.setScoreAndLevel(Score.getScore(), Medal.getLevel());
		setState(GameOver);
	}
	if (pauseActive) {
		setState(Pause);
	}
}

void Game::checkCollisions() {
	for (size_t i = 0; i < CatchingItem.getSprites().size(); ++i) {
		if (Player.getSprite().getGlobalBounds().intersects(CatchingItem.getSprite(i).getGlobalBounds())) {
			CatchingItem.removeItem(i);
			updateScore();
			SoundManager.playSound("bite", 70.0f);
			break; 
		}
	}
}

void Game::updateScore() {
	Score.increaseScore(10);
	if ((Score.getScore() - prevScore >= 200) && !Medal.IsLastLevelReached()) {
		Medal.setNextMedal();
		SoundManager.playSound("levelUp", 27.0f);
		CatchingItem.increaseSpeedByPercentage(15);
		prevScore = Score.getScore();
		pauseActive = true;
	}
	
}

void Game::resetGame() {
	Medal.reset();
	Health.reset();
	Score.reset();
	CatchingItem.reset();
	totalTime = 0;
	prevScore = 0;
	failSoundNotPlayed = false;
}

void Game::setState(GameState newState) {
	State = newState;
}

Game::GameState Game::getState() const {
	return State;
}