// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// (Adapted from past projects)

/**
 * @brief A class that encapsulates sound playback functionality using SFML.
 *
 * This class provides simple controls for loading, playing, pausing, and stopping sounds.
 * It also allows control over looping and volume.
 */
class SFMLSound {
 public:
  /**
   * @brief Constructs a sound object from a given file path.
   *
   * Initializes the sound by loading a sound file and setting optional playback settings
   * like looping and volume.
   *
   * @param filepath The path to the sound file to be loaded.
   * @param loop If true, the sound will loop when played (default is false).
   * @param volume The volume of the sound (default is 100.0f).
   *
   * @note Throws an exception if the sound file cannot be loaded.
   */
  explicit SFMLSound(const std::string& filepath, bool loop = false
      , float volume = 100.0f);

  /**
   * @brief Plays the sound.
   *
   * Starts or resumes the playback of the sound.
   */
  void play();

  /**
   * @brief Pauses the sound.
   *
   * Pauses the sound playback if it is currently playing.
   */
  void pause();

  /**
   * @brief Stops the sound.
   *
   * Stops the sound playback and resets the current playback position to the beginning.
   */
  void stop();

  /**
   * @brief Checks if the sound is currently playing.
   *
   * @return true if the sound is playing, false otherwise.
   */
  bool isPlaying() const;

  /**
   * @brief Sets the volume of the sound.
   *
   * @param volume The new volume of the sound, ranging from 0.0 (mute) to 100.0 (maximum volume).
   */
  void setVolume(float volume);

  /**
   * @brief Gets the current volume of the sound.
   *
   * @return The current volume, ranging from 0.0 (mute) to 100.0 (maximum volume).
   */
  float getVolume() const;

 private:
  /**
   * @brief The buffer holding the sound data.
   *
   * This stores the sound data loaded from the file.
   */
  sf::SoundBuffer buffer;

  /**
   * @brief The sound object responsible for playback.
   *
   * This manages the playback, including control over volume, looping, and other sound properties.
   */
  sf::Sound sound;

  /**
   * @brief Indicates whether the sound should loop during playback.
   */
  bool loop;
};
