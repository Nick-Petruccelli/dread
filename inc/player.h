#ifndef PLAYER_H
#define PLAYER_H
#include "gameObject.h"
#include <SDL2/SDL.h>
#include <string>

class Player : public GameObject {
public:
  Player();
  void handelEvents(SDL_Event e);
  void updateState();
  void move();

private:
  int mVelX;
  int mVelY;
  int mMaxVel;
};

#endif
