#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>

class GameObject {
public:
  GameObject();
  GameObject(int x, int y);
  ~GameObject();
  bool setTexture(std::string path, SDL_Renderer *renderer);
  void setPosition(float x, float y);
  void setCollider(int w, int h);
  void setCollider(int xOff, int yOff, int w, int h);
  virtual void handelEvents(SDL_Event e){};
  virtual void updateState(){};
  void render(int *camOffSet);
  SDL_Rect getCollider();
  int getPosX();
  int getPosY();
  int getWidth();
  int getHeight();
  unsigned int getID();
  Texture getTex();

protected:
  unsigned int mID;
  float mPosX;
  float mPosY;
  Texture mTexture;
  SDL_Rect mCollider;
};

#endif
