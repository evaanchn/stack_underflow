// Copyright 2025 stack_underflow CC-BY 4.0

#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>

#include <vector>
#include <string>

/// @brief Animates a gif with png frames, stored in a folder, numbered from 1
/// to frame amount (frame1.png, ..., frameN.png)
class AnimatedGIF {
 private:
  Fl_Box *gifBox = nullptr;
  std::vector<Fl_PNG_Image*> frames = {};
  int currentFrame = 0;
  double frameDelay = 0;  // in seconds

 public:
  explicit AnimatedGIF(double delay) : frameDelay(delay) {}
  ~AnimatedGIF();

 public:
  void createGIFBox(int x, int y, int w, int h);
  void setFrames(const std::string& path, int framesAmount);

  void start() {
    Fl::add_timeout(frameDelay, AnimatedGIF::timer_cb, this);
  }

  void stop() {
    Fl::remove_timeout(AnimatedGIF::timer_cb, this);
  }

 private:
  static void timer_cb(void *userdata) {
    AnimatedGIF* self = static_cast<AnimatedGIF*>(userdata);
    self->nextFrame();
    Fl::repeat_timeout(self->frameDelay, timer_cb, userdata);
  }

  void nextFrame();
};
