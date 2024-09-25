#ifndef PLAYER_H
#define PLAYER_H
#include "gameObject.h"
#include <SDL2/SDL.h>

class Player : public GameObject {
public:
  Player();
  ~Player();
  Player(float x, float y);
  void handelEvents(SDL_Event e) override;
  void updateState() override;
  void move();
  void setMaxVel(float vel);

private:
  float mVelX;
  float mVelY;
  float mMaxVel;
};

#endif
