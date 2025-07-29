//
// Created by david on 7/29/2025.
//

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class SoundManager {
private:
    SoundManager() = default;

    std::unordered_map<std::string, sf::SoundBuffer> buffers;
    std::vector<sf::Sound> sounds; // Keep sounds alive while playing

public:
    static SoundManager& getInstance();

    void loadSound(const std::string& name, const std::string& filepath);
    void playSound(const std::string& name);
    void cleanup();
};



#endif //SOUNDMANAGER_H
