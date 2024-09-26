#include "../inc/camera.h"
#include "../inc/engine.h"
#include "../inc/scene.h"
#include "../inc/window.h"
#include <cstdlib>

extern Scene gScene;
extern Window gWindow;

Camera::Camera() {
  mCam.x = 0;
  mCam.y = 0;
  mCam.w = 640;
  mCam.h = 480;
  mFollowSpeed = 5.0;
}

void Camera::moveTo(float x, float y) {
  float velX = (x - (mCam.x + mCam.w / 2.0)) * mFollowSpeed;
  float velY = (y - (mCam.y + mCam.h / 2.0)) * mFollowSpeed;
  float deltaX = velX * (Engine::getDeltaTime() / 1000.0);
  float deltaY = velY * (Engine::getDeltaTime() / 1000.0);
  mCam.x += deltaX;
  mCam.y += deltaY;
  if (mCam.x < 0 || mCam.x + mCam.w > gScene.getMapWidth()) {
    mCam.x -= deltaX;
  }
  if (mCam.y < 0 || mCam.y + mCam.h > gScene.getMapHeight()) {
    mCam.y -= deltaY;
  }
}

int *Camera::getOffSet() {
  int *out = new int[2];
  out[0] = mCam.x;
  out[1] = mCam.y;
  return out;
}
