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
public:
    static SoundManager& getInstance();

    void loadSound(const std::string& name, const std::string& filepath);
    void playSound(const std::string& name);

private:
    SoundManager();

    std::unordered_map<std::string, sf::SoundBuffer> buffers;

    std::unordered_map<std::string, std::vector<sf::Sound>> soundPool;
    const size_t maxVoicesPerSound = 10;
};



#endif //SOUNDMANAGER_H
