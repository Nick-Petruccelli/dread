#include "../inc/player.h"
#include "../inc/engine.h"

Player::Player() {
  mPosX = 100;
  mPosY = 150;
  mVelX = 0;
  mVelY = 0;
  mMaxVel = 1;
}

void Player::handelEvents(SDL_Event e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_w:
      mVelY -= mMaxVel;
      break;
    case SDLK_s:
      mVelY += mMaxVel;
      break;
    case SDLK_a:
      mVelX -= mMaxVel;
      break;
    case SDLK_d:
      mVelX += mMaxVel;
      break;
    };
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_w:
      mVelY += mMaxVel;
      break;
    case SDLK_s:
      mVelY -= mMaxVel;
      break;
    case SDLK_a:
      mVelX += mMaxVel;
      break;
    case SDLK_d:
      mVelX -= mMaxVel;
      break;
    };
  }
}

void Player::move() {
  float deltaTime = Engine::getDeltaTime() / 1000.0;
  float velAdjustX = mVelX * deltaTime;
  float velAdjustY = mVelY * deltaTime;
  float newPosX = mPosX + velAdjustX;
  float newPosY = mPosY + velAdjustY;

  unsigned int screenWidth = Engine::getScreenWidth();
  unsigned int screenHeight = Engine::getScreenHeight();
  if (newPosX < 0 || newPosX > screenWidth - mTexture.getWidth()) {
    newPosX -= velAdjustX;
  }
  if (newPosY < 0 || newPosY > screenHeight - mTexture.getHeight()) {
    newPosY -= velAdjustY;
  }

  mPosX = newPosX;
  mPosY = newPosY;
}

void Player::updateState() { move(); }
