#include "../inc/engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

unsigned int Engine::mDeltaTime = 0;
unsigned int Engine::mPrevFrameTime = SDL_GetTicks();
unsigned int Engine::mScreenWidth = 640;
unsigned int Engine::mScreenHeight = 480;

void Engine::init() {
  mDeltaTime = 0;
  mPrevFrameTime = SDL_GetTicks();
  mScreenWidth = 640;
  mScreenHeight = 480;
}

void Engine::updateDeltaTime() {
  mDeltaTime = SDL_GetTicks() - mPrevFrameTime;
  mPrevFrameTime = SDL_GetTicks();
}

unsigned int Engine::getScreenWidth() { return mScreenWidth; }

unsigned int Engine::getScreenHeight() { return mScreenHeight; }

unsigned int Engine::getDeltaTime() { return mDeltaTime; }
