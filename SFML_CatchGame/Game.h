#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "CatchingItem.h"
#include "Health.h"
#include "Score.h"
#include "Medal.h"
#include "Menu.h"
#include "SoundManager.h";

class Game
{
public:
	Game();
	void run();
	enum GameState {
		MainMenu,
		GameOver,
		Reseting,
		Playing,
		Pause
	};

public:
	void setState(GameState newState);
	GameState getState() const;

private:
	void processEvents();
	void update();
	void render();
	void checkCollisions();
	bool isGameOver();
	void checkGameState();
	void resetGame();
	void updateScore();

private:
	sf::RenderWindow Window;
	unsigned long prevScore = 0;
	Menu Menu;
	Player Player;
	Health Health;
	CatchingItem CatchingItem;
	Score Score;
	Medal Medal;
	sf::Clock clock;
	GameState State;
	bool pauseActive;
	float totalTime;
	SoundManager SoundManager;
	bool failSoundNotPlayed;
};

