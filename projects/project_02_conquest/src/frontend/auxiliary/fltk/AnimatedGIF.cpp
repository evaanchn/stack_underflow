// Copyright 2025 stack_underflow CC-BY 4.0

#include "AnimatedGIF.hpp"

AnimatedGIF::~AnimatedGIF() {
  for (auto* frame : this->frames) if (frame) delete frame;
  delete this->gifBox;
}

void AnimatedGIF::createGIFBox(int x, int y, int w, int h) {
  this->gifBox = new Fl_Box(x, y, w, h);
}

void AnimatedGIF::setFrames(const std::string& path, int framesAmount) {
  this->frames.resize(framesAmount);
  for (int frameIdx = 0; frameIdx < framesAmount; ++frameIdx) {
    std::string framePath = path + "frame" + std::to_string(frameIdx + 1)
        + ".png";
    this->frames[frameIdx] = new Fl_PNG_Image(framePath.c_str());
  }
}

void AnimatedGIF::nextFrame() {
  this->currentFrame = (this->currentFrame + 1) % this->frames.size();
  gifBox->image(frames[this->currentFrame]);
  gifBox->redraw();
}
