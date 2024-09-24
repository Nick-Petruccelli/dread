#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>

class GameObject {
public:
  GameObject();
  ~GameObject();
  bool setTexture(std::string path, SDL_Renderer *renderer);
  void setCollider(int w, int h);
  void setCollider(int xOff, int yOff, int w, int h);
  void setID(unsigned int id);
  void handelEvents(SDL_Event e);
  void updateState();
  void render();
  SDL_Rect getCollider();
  int getPosX();
  int getPosY();
  unsigned int getID();

protected:
  unsigned int mID;
  float mPosX;
  float mPosY;
  Texture mTexture;
  SDL_Rect mCollider;
};

#endif
