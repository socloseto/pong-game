#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <string>
#include <algorithm>

class AudioManager {
public:
    static AudioManager& instance();
    bool loadSoundFromMemory(const std::string& name, const unsigned char* data, size_t size);
    void loadAllEmbeddedAssets();
    void playSound(const std::string& name);
    void update();
    void setupMainMusic(sf::Music& music);
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