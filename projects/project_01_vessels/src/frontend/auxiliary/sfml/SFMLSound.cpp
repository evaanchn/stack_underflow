// Copyright 2025 stack_underflow CC-BY 4.0

#include "SFMLSound.hpp"

SFMLSound::SFMLSound(const std::string& filepath, bool loop, float volume) :
    loop(loop) {
  if (!buffer.loadFromFile(filepath)) {
    throw std::runtime_error("SOUND ERROR: Could not load sound file: " +
        filepath);
  }
  sound.setBuffer(buffer);
  sound.setLoop(loop);
  sound.setVolume(volume);
}

void SFMLSound::play() {
  if (!isPlaying()) sound.play();
}

void SFMLSound::pause() {
  sound.pause();
}

void SFMLSound::stop() {
  sound.stop();
}

bool SFMLSound::isPlaying() const {
  return sound.getStatus() == sf::Sound::Playing;
}

void SFMLSound::setVolume(float volume) {
  sound.setVolume(volume);
}

float SFMLSound::getVolume() const {
  return sound.getVolume();
}