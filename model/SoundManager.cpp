//
// Created by david on 7/29/2025.
//

#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::loadSound(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sound: " << filepath << "\n";
        return;
    }
    buffers[name] = buffer;
}

void SoundManager::playSound(const std::string& name) {
    auto it = buffers.find(name);
    if (it == buffers.end()) return;

    sounds.emplace_back(); // constructs directly in the vector
    sf::Sound& sound = sounds.back();
    sound.setBuffer(it->second);
    sound.play();
}

void SoundManager::cleanup() {
    sounds.erase(std::remove_if(sounds.begin(), sounds.end(),
        [](const sf::Sound& s) {
            return s.getStatus() == sf::Sound::Stopped;
        }),
        sounds.end());
}