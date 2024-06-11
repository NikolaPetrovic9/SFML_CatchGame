#pragma once

#include <iostream>
#include <unordered_map>
#include "SFML/Audio.hpp"

class SoundManager
{
public:
	SoundManager();

	void playSound(std::string soundName, float volume);

private:
	bool loadSound(const std::string& key, const std::string& filename);

private:
	std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
	std::unordered_map<std::string, sf::Sound> sounds;
};

