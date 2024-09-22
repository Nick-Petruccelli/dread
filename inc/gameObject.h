#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "texture.h"
#include <SDL2/SDL.h>
#include <string>

class GameObject {
public:
  GameObject();
  ~GameObject();
  bool setTexture(std::string path);
  void setCollider(int w, int h);
  void setCollider(int xOff, int yOff, int w, int h);
  void handelEvents(SDL_Event e);
  void updateState();
  void render();
  SDL_Rect getCollider();
  int getPosX();
  int getPosY();

private:
  int mPosX;
  int mPosY;
  Texture mTexture;
  SDL_Rect mCollider;
};

#endif
