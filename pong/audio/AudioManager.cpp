#include "AudioManager.h"

AudioManager& AudioManager::instance() {
	static AudioManager inst;
	return inst;
}

bool AudioManager::loadSound(const std::string& name, const std::string& filename) {
	sf::SoundBuffer buffer;
	if (buffer.loadFromFile(filename)) {
		buffers_[name] = std::move(buffer);
		return true;
	}
	return false;
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

void AudioManager::setMainMusic(sf::Music* music) {
	mainMusic_ = music;
}

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