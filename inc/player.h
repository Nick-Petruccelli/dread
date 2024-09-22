#ifndef PLAYER_H
#define PLAYER_H
#include "gameObject.h"
#include <SDL2/SDL.h>

class Player : public GameObject {
public:
  Player(float x, float y);
  void handelEvents(SDL_Event e);
  void updateState();
  void move();

private:
  float mVelX;
  float mVelY;
  float mMaxVel;
};

#endif
