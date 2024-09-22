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
  unsigned int deltaTime = Engine::getDeltaTime();
  int velAdjustX = mVelX * deltaTime;
  int velAdjustY = mVelY * deltaTime;
  mPosX += velAdjustX;
  mPosY += velAdjustY;

  unsigned int screenWidth = Engine::getScreenWidth();
  unsigned int screenHeight = Engine::getScreenHeight();
  if (mPosX < 0 || mPosX > screenWidth - mTexture.getWidth()) {
    mPosX -= velAdjustX;
  }
  if (mPosY < 0 || mPosY > screenHeight - mTexture.getHeight()) {
    mPosY -= velAdjustY;
  }
}

void Player::updateState() { move(); }
