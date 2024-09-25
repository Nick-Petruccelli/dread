#include "../inc/gameObject.h"
#include <SDL2/SDL_render.h>

GameObject::GameObject() {}

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

void GameObject::setID(unsigned int id) { mID = id; }

void GameObject::render() {
  if (mTexture.isLoaded()) {
    mTexture.render((int)mPosX, (int)mPosY);
  }
}

bool Texture::isLoaded() { return mTexture != NULL; }

SDL_Rect GameObject::getCollider() { return mCollider; }
int GameObject::getPosX() { return mPosX; }
int GameObject::getPosY() { return mPosY; }
unsigned int GameObject::getID() { return mID; }
