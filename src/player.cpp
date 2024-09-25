#include "../inc/player.h"
#include "../inc/engine.h"
#include "../inc/window.h"
#include <cmath>

extern Window gWindow;

Player::Player() {}
Player::~Player() {}

Player::Player(float x, float y) {
  mPosX = x;
  mPosY = y;
  mVelX = 0;
  mVelY = 0;
  mMaxVel = 10;
}

void Player::setMaxVel(float vel) { mMaxVel = vel; }

void Player::handelEvents(SDL_Event e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_w:
      mVelY -= 1;
      break;
    case SDLK_s:
      mVelY += 1;
      break;
    case SDLK_a:
      mVelX -= 1;
      break;
    case SDLK_d:
      mVelX += 1;
      break;
    };
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_w:
      mVelY += 1;
      break;
    case SDLK_s:
      mVelY -= 1;
      break;
    case SDLK_a:
      mVelX += 1;
      break;
    case SDLK_d:
      mVelX -= 1;
      break;
    };
  }
}

void Player::updateState() { move(); }

void Player::move() {
  if (mVelX == 0 && mVelY == 0) {
    return;
  }

  float deltaTime = Engine::getDeltaTime() / 1000.0;
  float velAdjustX =
      ((mVelX * mMaxVel) / (sqrtf(mVelX * mVelX + mVelY * mVelY))) * deltaTime;
  float velAdjustY =
      ((mVelY * mMaxVel) / (sqrtf(mVelX * mVelX + mVelY * mVelY))) * deltaTime;
  mPosX += velAdjustX;
  mPosY += velAdjustY;

  float windowScale = gWindow.getScale();
  unsigned int screenWidth = gWindow.getWidth() / windowScale;
  unsigned int screenHeight = gWindow.getHeight() / windowScale;
  if (mPosX < 0 || mPosX > screenWidth - mTexture.getWidth()) {
    mPosX -= velAdjustX;
  }
  if (mPosY < 0 || mPosY > screenHeight - mTexture.getHeight()) {
    mPosY -= velAdjustY;
  }
  printf("dt: %f\nvx: %f\nvy: %f\nposx: %f\nposy: %f\n", deltaTime, velAdjustX,
         velAdjustY, mPosX, mPosY);
}
