//
// Created by david on 7/29/2025.
//

#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager() = default;

void SoundManager::loadSound(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sound: " << filepath << "\n";
        return;
    }

    buffers[name] = std::move(buffer);
    soundPool[name] = std::vector<sf::Sound>(maxVoicesPerSound);
    for (auto& sound : soundPool[name]) {
        sound.setBuffer(buffers[name]);
    }
}

void SoundManager::playSound(const std::string& name) {
    auto bufferIt = buffers.find(name);
    auto poolIt = soundPool.find(name);
    if (bufferIt == buffers.end() || poolIt == soundPool.end()) return;

    std::vector<sf::Sound>& pool = poolIt->second;

    // First try to find a free sound
    for (auto& sound : pool) {
        if (sound.getStatus() != sf::Sound::Playing) {
            sound.play();
            return;
        }
    }

    // All sounds are busy — reuse the oldest one
    sf::Time oldest = pool[0].getPlayingOffset();
    size_t oldestIndex = 0;

    for (size_t i = 1; i < pool.size(); ++i) {
        if (pool[i].getPlayingOffset() > oldest) {
            oldest = pool[i].getPlayingOffset();
            oldestIndex = i;
        }
    }

    pool[oldestIndex].stop(); // stop current sound
    pool[oldestIndex].play(); // restart with same buffer
}