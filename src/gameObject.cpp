#include "../inc/gameObject.h"
#include <SDL2/SDL_render.h>

GameObject::GameObject() {}
GameObject::GameObject(int x, int y) : mPosX(x), mPosY(y) {}

GameObject::~GameObject() {}

Texture GameObject::getTex() { return mTexture; }

bool GameObject::setTexture(std::string path, SDL_Renderer *renderer) {
  mTexture.setRenderer(renderer);
  if (!mTexture.loadFromFile(path)) {
    return false;
  }
  return true;
}

void GameObject::setPosition(float x, float y) {
  mPosX = x;
  mPosY = y;
}

void GameObject::setCollider(int w, int h) {
  mCollider.x = mPosX;
  mCollider.y = mPosY;
  mCollider.w = w;
  mCollider.h = h;
}
void GameObject::setCollider(int xOff, int yOff, int w, int h) {
  mCollider.x = mPosX + xOff;
  mCollider.y = mPosY + yOff;
  mCollider.w = w;
  mCollider.h = h;
}

void GameObject::render(int *camOffSet) {
  if (mTexture.isLoaded()) {
    mTexture.render((int)mPosX, (int)mPosY, camOffSet);
  }
}

bool Texture::isLoaded() { return mTexture != NULL; }

SDL_Rect GameObject::getCollider() { return mCollider; }
int GameObject::getPosX() { return mPosX; }
int GameObject::getPosY() { return mPosY; }
int GameObject::getWidth() { return mTexture.getWidth(); }
int GameObject::getHeight() { return mTexture.getHeight(); }
unsigned int GameObject::getID() { return mID; }
