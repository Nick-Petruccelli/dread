#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

class Camera {
public:
  Camera();
  void updateState();
  void moveTo(float x, float y);
  int *getOffSet();

private:
  SDL_Rect mCam;
  float mFollowSpeed;
};

#endif
