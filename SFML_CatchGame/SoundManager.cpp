#include "SoundManager.h"

SoundManager::SoundManager()
{
    loadSound("click", "Assets/Music/click-button.mp3");
    loadSound("bite", "Assets/Music/crunchy-bite.mp3");
    loadSound("levelUp", "Assets/Music/game-level-complete.mp3");
    loadSound("fail", "Assets/Music/fail.mp3");
   
}

bool SoundManager::loadSound(const std::string& key, const std::string& filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename))
    {
        return false;
    }
    soundBuffers[key] = buffer;
    sf::Sound sound;
    sound.setBuffer(soundBuffers[key]);
    sounds[key] = sound;
    return true;
}

void SoundManager::playSound(std::string soundName, float volume)
{
    if (sounds.find(soundName) != sounds.end())
    {
        sounds[soundName].setVolume(volume);
        sounds[soundName].play();
    }
}