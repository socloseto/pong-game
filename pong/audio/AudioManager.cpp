#include "AudioManager.h"

#include "../assets/audio/goal_ogg.h"
#include "../assets/audio/hit_ogg.h"
#include "../assets/audio/lose_ogg.h"
#include "../assets/audio/mainTheme_ogg.h"
#include "../assets/audio/missedGoal_ogg.h"
#include "../assets/audio/win_ogg.h"

AudioManager& AudioManager::instance() {
  static AudioManager inst;
  return inst;
}

bool AudioManager::loadSoundFromMemory(const std::string& name,
                                       const unsigned char* data, size_t size) {
  sf::SoundBuffer buffer;
  if (buffer.loadFromMemory(data, size)) {
    buffers_[name] = std::move(buffer);
    return true;
  }
  return false;
}
void AudioManager::loadAllEmbeddedAssets() {
  loadSoundFromMemory("goal", goal_ogg, goal_ogg_len);
  loadSoundFromMemory("hit", hit_ogg, hit_ogg_len);
  loadSoundFromMemory("lose", lose_ogg, lose_ogg_len);
  loadSoundFromMemory("miss", missedGoal_ogg, missedGoal_ogg_len);
  loadSoundFromMemory("win", win_ogg, win_ogg_len);
}
void AudioManager::playSound(const std::string& name) {
  auto it = buffers_.find(name);
  if (it != buffers_.end()) {
    activeSounds_.emplace_back(it->second);
    activeSounds_.back().setVolume(volume_);
    activeSounds_.back().play();
  }
}

void AudioManager::update() {
  activeSounds_.remove_if([](const sf::Sound& s) {
    return s.getStatus() == sf::SoundSource::Status::Stopped;
  });
}
void AudioManager::setupMainMusic(sf::Music& music) {
  if (music.openFromMemory(mainTheme_ogg, mainTheme_ogg_len)) {
    music.setLooping(true);
    this->setMainMusic(&music);
    music.play();
  }
}
void AudioManager::setMainMusic(sf::Music* music) { mainMusic_ = music; }

void AudioManager::setVolume(float volume) {
  volume_ = std::clamp(volume, 0.f, 100.f);
  for (auto& s : activeSounds_) {
    s.setVolume(volume_);
  }
  if (mainMusic_) {
    mainMusic_->setVolume(volume_);
  }
}

float AudioManager::getVolume() const { return volume_; }