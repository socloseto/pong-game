#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <string>
#include <algorithm>

class AudioManager {
public:
    static AudioManager& instance();

    bool loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
    void update();

    void setMainMusic(sf::Music* music);
    void setVolume(float volume);
    float getVolume() const;

private:
    AudioManager() = default;
    std::map<std::string, sf::SoundBuffer> buffers_;
    std::list<sf::Sound> activeSounds_;
    sf::Music* mainMusic_ = nullptr;
    float volume_ = 100.f;
};